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
#include <osgEarth/TileHandler>
#include <osgEarth/ImageLayer>
#include <osgEarth/ElevationLayer>
#include <osgEarth/ImageToHeightFieldConverter>
#include <osgEarth/ImageUtils>
#include <osgEarth/FileUtils>

#include <osgDB/WriteFile>
#include <osgDB/FileUtils>


using namespace osgEarth;

bool TileHandler::handleTile(const TileKey& key)
{
    return true;
}

bool TileHandler::hasData( const TileKey& key ) const
{
    return true;
}
        
std::string TileHandler::getProcessString() const
{
    return "";
}
