/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
* Copyright 2008-2013 Pelican Mapping
* http://osgearth.org
*
* osgEarth is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include <osgEarthUtil/LogarithmicDepthBuffer>
#include <osgEarth/CullingUtils>
#include <osgEarth/VirtualProgram>
#include <osgUtil/CullVisitor>
#include <osg/Uniform>
#include <osg/buffered_value>

#define LC "[LogarithmicDepthBuffer] "

using namespace osgEarth;
using namespace osgEarth::Util;

//------------------------------------------------------------------------

namespace
{
    struct LogDepthCullCallback : public osg::NodeCallback
    {
        void operator()(osg::Node* node, osg::NodeVisitor* nv)
        {
            osgUtil::CullVisitor* cv = Culling::asCullVisitor(nv);
            osg::Camera* camera = cv->getCurrentCamera();
            if ( camera )
            {
                // find (or create) a stateset
                unsigned id = camera->getGraphicsContext()->getState()->getContextID();
                osg::ref_ptr<osg::StateSet>& stateset = _stateSets[id];
                if ( !stateset.valid() )
                    stateset = new osg::StateSet();

                // the uniform conveying the far clip plane:
                osg::Uniform* u = stateset->getOrCreateUniform("oe_logdepth_farplane", osg::Uniform::FLOAT);

                // calculate the far plane based on the camera location:
                osg::Vec3d E, C, U;
                camera->getViewMatrixAsLookAt(E, C, U);                
                double farplane = E.length() + 1e6;
                
                // set for culling purposes:
                double L, R, B, T, N, F;
                camera->getProjectionMatrixAsFrustum(L, R, B, T, N, F);                
                camera->setProjectionMatrixAsFrustum(L, R, B, T, N, farplane);

                // communicate to the shader:
                u->set( (float)farplane );

                // and continue traversal of the camera's subgraph.
                cv->pushStateSet( stateset );
                traverse(node, nv);
                cv->popStateSet();
            }
            else
            {                    
                traverse(node, nv);
            }
        }

        // context-specific stateset collection
        osg::buffered_value<osg::ref_ptr<osg::StateSet> > _stateSets;
    };

    const char* vertexSource =
        "#version " GLSL_VERSION_STR "\n"
        GLSL_DEFAULT_PRECISION_FLOAT "\n"
        "uniform float oe_logdepth_farplane; \n"
        "void oe_logdepth_vert(inout vec4 clip) \n"
        "{ \n"
        "    const float C = 0.0005; \n"
        "    clip.z = (2.0*log2(C*clip.w+1.0)/log2(C*oe_logdepth_farplane+1.0)-1.0)*clip.w;\n"
        "} \n";

    // NOTE: to do this properly we also need a fragment program that clamps depth
    // so we don't clip polygons that cross the near plane. But that will disable
    // early Z check so we will look into that later. -gw
}

//------------------------------------------------------------------------

LogarithmicDepthBuffer::LogarithmicDepthBuffer()
{
    _cullCallback = new LogDepthCullCallback();
}

void
LogarithmicDepthBuffer::install(osg::Camera* camera)
{
    if ( camera )
    {
        // install the shader component:
        osg::StateSet* stateset = camera->getOrCreateStateSet();
        
        VirtualProgram* vp = VirtualProgram::getOrCreate( stateset );
        vp->setFunction( "oe_logdepth_vert", vertexSource, ShaderComp::LOCATION_VERTEX_CLIP, FLT_MAX );

        // configure the camera:
        camera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);

        // install a cull callback to control the far plane:
        camera->addCullCallback( _cullCallback.get() );
    }
}

void
LogarithmicDepthBuffer::uninstall(osg::Camera* camera)
{
    if ( camera )
    {
        camera->removeCullCallback( _cullCallback.get() );

        osg::StateSet* stateset = camera->getStateSet();
        if ( stateset )
        {
            VirtualProgram* vp = VirtualProgram::get( camera->getStateSet() );
            if ( vp )
            {
                vp->removeShader( "oe_logdepth_vert" );
            }

            stateset->removeUniform( "oe_logdepth_farplane" );
        }
    }
}
