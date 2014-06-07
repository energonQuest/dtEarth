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
#include "KML_LineString"

using namespace osgEarth_kml;

void
KML_LineString::parseStyle( const Config& conf, KMLContext& cs, Style& style )
{
    KML_Geometry::parseStyle(conf, cs, style);

    // need a line symbol minimally
    LineSymbol* line = style.get<LineSymbol>();
    if ( !line )
    {
        line = style.getOrCreate<LineSymbol>();
        line->stroke()->color() = osg::Vec4f(1,1,1,1);
    }

    if ( conf.value("tessellate") == "1" )
    {
        line->tessellation() = 20; // KML default
    }
}

void
KML_LineString::parseCoords( const Config& conf, KMLContext& cx )
{
    _geom = new LineString();
    KML_Geometry::parseCoords( conf, cx );
}
