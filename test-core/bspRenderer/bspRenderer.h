/**
 * \file BSPRenderer.h
 * \brief Renders scene using BSP-tree
 *
 * \ingroup ?
 * \date Dec, 2018
 * \author Mark Kovalev
 */

#ifndef BSPRENDERER_H
#define BSPRENDERER_H

#include <iterator>
#include <iostream>
#include <climits>
#include <cfloat>
#include <fstream>

#include "core/geometry/polygons.h"
#include "core/geometry/line.h"

#include "core/utils/global.h"

#include "core/buffers/bufferFactory.h"
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/buffers/rgb24/abstractPainter.h"
#include "core/fileformats/bmpLoader.h"


#define DEBUG 0

#if 1

namespace corecvs {

namespace BSPRenderer {

struct Linedef {
    int sidedef;
};

struct Sector {
    vector<Linedef> linedefs;
    Polygon space;
};

struct Level {
    vector<Sector> sectors;
};

class BSPNode2d {
public:
    Ray2d       *separator = nullptr;
    Polygon     leftBoundingBox,
                rightBoundingBox;
    BSPNode2d   *leftTree = nullptr,
                *rightTree = nullptr;
    Sector      *leftSector = nullptr,
                *rightSector = nullptr;
    int         nodeDepth,
                nodeNumber;

    BSPNode2d() {}

    BSPNode2d(Level& level, int depth, int number)
    {
        nodeDepth = depth;
        nodeNumber = number;
        BSPNodeBuilder(level);
    }

private:
    void BSPNodeBuilder(Level& level);

    int SplitLevel(Level& level, Ray2d& separator,
                   Level& leftPart, Level& rightPart,
                   std::ofstream& log);

    bool SplitSector(Sector& sector, Line2d& sepLine,
                     Vector2dd& enterPt, Vector2dd& exitPt,
                     Sector& leftPart, Sector& rightPart,
                     std::ofstream& log);

    Sector SectorFromPoly(Polygon& poly, vector<Linedef>& origLinedefs,
                          int& startIdx, int& endIdx,
                          Vector2dd& startPt, Vector2dd& endPt,
                          std::ofstream& log);

    Polygon GetBoundingBox(Level& level);
};

bool OnSegment(Segment2d& segment, const Vector2dd& point);

void DrawSector(Sector& sector, RGB24Buffer& buffer,
                bool withInfo = false);

void DrawSector(BSPNode2d& node, RGB24Buffer& buffer,
                bool withInfo = false);

void DrawLevel(Level& level, RGB24Buffer& buffer,
               bool withInfo = false);

void DrawBSPNode(BSPNode2d& node, RGB24Buffer& buffer,
                 bool withInfo = false);

} // namespace BSPRenderer

} // namespace corecvs

#endif

#endif // BSPRENDERER_H
