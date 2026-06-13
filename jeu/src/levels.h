#ifndef LEVELS_H
#define LEVELS_H

#include "graphics.h"

struct Level {
  int startX, startY;
  int portalX, portalY;
  int enemyCount;
  int enemyType[5];
  int enemyX[5];
  int enemyY[5];
  int obstacleCount;
  int obstacleType[6];
  int obstacleX[6];
  int obstacleY[6];
};

Level levels[3] = {

  {
    GRID_OFFSET_X + 0 * TILE_SIZE, GRID_OFFSET_Y + 4 * TILE_SIZE,
    GRID_OFFSET_X + 7 * TILE_SIZE, GRID_OFFSET_Y + 0 * TILE_SIZE,
    0,
    {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0},
    5,
    {0, 1, 0, 2, 1},
    {
      GRID_OFFSET_X + 1 * TILE_SIZE,
      GRID_OFFSET_X + 4 * TILE_SIZE,
      GRID_OFFSET_X + 3 * TILE_SIZE,
      GRID_OFFSET_X + 2 * TILE_SIZE,
      GRID_OFFSET_X + 5 * TILE_SIZE
    },
    {
      GRID_OFFSET_Y + 3 * TILE_SIZE,
      GRID_OFFSET_Y + 3 * TILE_SIZE,
      GRID_OFFSET_Y + 2 * TILE_SIZE,
      GRID_OFFSET_Y + 1 * TILE_SIZE,
      GRID_OFFSET_Y + 1 * TILE_SIZE
    }
  },

  {
    GRID_OFFSET_X + 0 * TILE_SIZE, GRID_OFFSET_Y + 2 * TILE_SIZE,
    GRID_OFFSET_X + 5 * TILE_SIZE, GRID_OFFSET_Y + 4 * TILE_SIZE,
    2,
    {0, 1},
    { GRID_OFFSET_X + 6 * TILE_SIZE, GRID_OFFSET_X + 3 * TILE_SIZE },
    { GRID_OFFSET_Y + 3 * TILE_SIZE, GRID_OFFSET_Y + 1 * TILE_SIZE },
    5,
    {0, 1, 2, 1, 0},
    {
      GRID_OFFSET_X + 4 * TILE_SIZE,
      GRID_OFFSET_X + 5 * TILE_SIZE,
      GRID_OFFSET_X + 2 * TILE_SIZE,
      GRID_OFFSET_X + 1 * TILE_SIZE,
      GRID_OFFSET_X + 2 * TILE_SIZE
    },
    {
      GRID_OFFSET_Y + 4 * TILE_SIZE,
      GRID_OFFSET_Y + 3 * TILE_SIZE,
      GRID_OFFSET_Y + 2 * TILE_SIZE,
      GRID_OFFSET_Y + 1 * TILE_SIZE,
      GRID_OFFSET_Y + 0 * TILE_SIZE
    }
  },

  {
    GRID_OFFSET_X + 0 * TILE_SIZE, GRID_OFFSET_Y + 0 * TILE_SIZE,
    GRID_OFFSET_X + 7 * TILE_SIZE, GRID_OFFSET_Y + 4 * TILE_SIZE,
    4,
    {0, 1, 0, 1},
    {
      GRID_OFFSET_X + 2 * TILE_SIZE,
      GRID_OFFSET_X + 3 * TILE_SIZE,
      GRID_OFFSET_X + 5 * TILE_SIZE,
      GRID_OFFSET_X + 6 * TILE_SIZE
    },
    {
      GRID_OFFSET_Y + 0 * TILE_SIZE,
      GRID_OFFSET_Y + 1 * TILE_SIZE,
      GRID_OFFSET_Y + 3 * TILE_SIZE,
      GRID_OFFSET_Y + 4 * TILE_SIZE
    },
    6,
    {2, 1, 0, 2, 1, 0},
    {
      GRID_OFFSET_X + 2 * TILE_SIZE,
      GRID_OFFSET_X + 3 * TILE_SIZE,
      GRID_OFFSET_X + 1 * TILE_SIZE,
      GRID_OFFSET_X + 1 * TILE_SIZE,
      GRID_OFFSET_X + 5 * TILE_SIZE,
      GRID_OFFSET_X + 4 * TILE_SIZE
    },
    {
      GRID_OFFSET_Y + 4 * TILE_SIZE,
      GRID_OFFSET_Y + 2 * TILE_SIZE,
      GRID_OFFSET_Y + 3 * TILE_SIZE,
      GRID_OFFSET_Y + 1 * TILE_SIZE,
      GRID_OFFSET_Y + 1 * TILE_SIZE,
      GRID_OFFSET_Y + 0 * TILE_SIZE
    }
  }
};

#endif