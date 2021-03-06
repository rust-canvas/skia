/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkLatticeIter_DEFINED
#define SkLatticeIter_DEFINED

#include "SkCanvas.h"
#include "SkScalar.h"
#include "SkTArray.h"

struct SkIRect;
struct SkRect;

/**
 *  Disect a lattice request into an sequence of src-rect / dst-rect pairs
 */
class SK_API SkLatticeIter {
public:

    static bool Valid(int imageWidth, int imageHeight, const SkCanvas::Lattice& lattice);

    SkLatticeIter(const SkCanvas::Lattice& lattice, const SkRect& dst);

    static bool Valid(int imageWidth, int imageHeight, const SkIRect& center);

    SkLatticeIter(int imageWidth, int imageHeight, const SkIRect& center, const SkRect& dst);

    /**
     *  While it returns true, use src/dst to draw the image/bitmap. Optional parameters
     *  isFixedColor and fixedColor specify if the rectangle is filled with a fixed color.
     *  If (*isFixedColor) is true, then (*fixedColor) contains the rectangle color.
     */
    bool next(SkRect* src, SkRect* dst, bool* isFixedColor = nullptr,
              SkColor* fixedColor = nullptr);

    /**
     *  Apply a matrix to the dst points.
     */
    void mapDstScaleTranslate(const SkMatrix& matrix);

    /**
     *  Returns the number of rects that will actually be drawn.
     */
    int numRectsToDraw() const {
        return fNumRectsToDraw;
    }

private:
    SkTArray<SkScalar> fSrcX;
    SkTArray<SkScalar> fSrcY;
    SkTArray<SkScalar> fDstX;
    SkTArray<SkScalar> fDstY;
    SkTArray<SkCanvas::Lattice::RectType> fRectTypes;
    SkTArray<SkColor> fColors;

    int  fCurrX;
    int  fCurrY;
    int  fNumRectsInLattice;
    int  fNumRectsToDraw;
};

#endif
