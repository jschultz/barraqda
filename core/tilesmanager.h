/***************************************************************************
 *   Copyright (C) 2012 by Mailson Menezes <mailson@gmail.com>             *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _OKULAR_TILES_MANAGER_H_
#define _OKULAR_TILES_MANAGER_H_

#include "okular_export.h"
#include "area.h"

#define TILES_MAXSIZE 2000000

class QPixmap;

namespace Okular {

class OKULAR_EXPORT Tile
{
    public:
        Tile();

        bool isValid() const;

        NormalizedRect rect;
        QPixmap *pixmap;
        uint dirty : 1;

        Tile *tiles;
        int nTiles;

        Tile *parent;
        int miss;
};

class OKULAR_EXPORT TilesManager
{
    public:
        TilesManager( int width, int height, Rotation rotation = Rotation0 );
        virtual ~TilesManager();

        void setPixmap( const QPixmap *pixmap, const NormalizedRect &rect );
        bool hasPixmap( const NormalizedRect &rect );
        QList<Tile> tilesAt( const NormalizedRect &rect );
        long totalMemory() const;
        void cleanupPixmapMemory( qulonglong numberOfBytes = 1 );

        int width() const;
        void setWidth( int width );
        int height() const;
        void setHeight( int height );
        Rotation rotation() const;
        void setRotation( Rotation rotation );

        static NormalizedRect toRotatedRect( const NormalizedRect &rect, Rotation rotation );
        static NormalizedRect fromRotatedRect( const NormalizedRect &rect, Rotation rotation );

    private:
        class Private;
        Private * const d;
        friend class Private;
};

}

#endif // _OKULAR_TILES_MANAGER_H_