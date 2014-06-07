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
#include <osgEarthSymbology/RenderSymbol>
#include <osgEarthSymbology/Style>

using namespace osgEarth;
using namespace osgEarth::Symbology;

OSGEARTH_REGISTER_SIMPLE_SYMBOL(render, RenderSymbol);

RenderSymbol::RenderSymbol(const Config& conf) :
Symbol          ( conf ),
_depthTest      ( true ),
_lighting       ( true ),
_backfaceCulling( true )
{
    mergeConfig(conf);
}

Config 
RenderSymbol::getConfig() const
{
    Config conf = Symbol::getConfig();
    conf.key() = "render";
    conf.addIfSet   ( "depth_test",       _depthTest );
    conf.addIfSet   ( "lighting",         _lighting );
    conf.addObjIfSet( "depth_offset",     _depthOffset );
    conf.addIfSet   ( "backface_culling", _backfaceCulling );
    return conf;
}

void 
RenderSymbol::mergeConfig( const Config& conf )
{
    conf.getIfSet   ( "depth_test",       _depthTest );
    conf.getIfSet   ( "lighting",         _lighting );
    conf.getObjIfSet( "depth_offset",     _depthOffset );
    conf.getIfSet   ( "backface_culling", _backfaceCulling );
}

void
RenderSymbol::parseSLD(const Config& c, Style& style)
{
    RenderSymbol defaults;

    if ( match(c.key(), "render-depth-test") ) {
        style.getOrCreate<RenderSymbol>()->depthTest() = as<bool>(c.value(), *defaults.depthTest());
    }
    else if ( match(c.key(), "render-lighting") ) {
        style.getOrCreate<RenderSymbol>()->lighting() = as<bool>(c.value(), *defaults.lighting());
    }
    else if ( match(c.key(), "render-depth-offset") ) {
        style.getOrCreate<RenderSymbol>()->depthOffset()->enabled() = as<bool>(c.value(), *defaults.depthOffset()->enabled() );
    }
    else if ( match(c.key(), "render-depth-offset-min-bias") ) {
        style.getOrCreate<RenderSymbol>()->depthOffset()->minBias() = as<float>(c.value(), *defaults.depthOffset()->minBias() );
        style.getOrCreate<RenderSymbol>()->depthOffset()->automatic() = false;
    }
    else if ( match(c.key(), "render-depth-offset-max-bias") ) {
        style.getOrCreate<RenderSymbol>()->depthOffset()->maxBias() = as<float>(c.value(), *defaults.depthOffset()->maxBias() );
    }
    else if ( match(c.key(), "render-depth-offset-min-range") ) {
        style.getOrCreate<RenderSymbol>()->depthOffset()->minRange() = as<float>(c.value(), *defaults.depthOffset()->minRange() );
    }
    else if ( match(c.key(), "render-depth-offset-max-range") ) {
        style.getOrCreate<RenderSymbol>()->depthOffset()->maxRange() = as<float>(c.value(), *defaults.depthOffset()->maxRange() );
    }
    else if ( match(c.key(), "render-depth-offset-auto") ) {
        style.getOrCreate<RenderSymbol>()->depthOffset()->automatic() = as<bool>(c.value(), *defaults.depthOffset()->automatic() );
    }
    else if ( match(c.key(), "render-backface-culling") ) {
        style.getOrCreate<RenderSymbol>()->backfaceCulling() = as<bool>(c.value(), *defaults.backfaceCulling() );
    }
}
