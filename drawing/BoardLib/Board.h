/* -*- mode: c++ -*- */
/**
 * @file   Board.h
 * @author Sebastien Fourey <http://www.greyc.ensicaen.fr/~seb>
 * @date   Sat Aug 18 2007
 * 
 * @brief  
 * @copyright
 * Copyright or © or Copr. Sébastien Fourey
 * 
 * Sébastien.Fourey - http://www.greyc.ensicaen.fr/~seb
 * 
 * 
 * This source code is part of the Board project, a C++ library whose
 * purpose is to allow simple drawings in EPS, FIG or SVG files.
 * 
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-C
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 * 
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms
 * 
 * Copyright or © or Copr. Sébastien Fourey
 * 
 * Sébastien.Fourey - http://www.greyc.ensicaen.fr/~seb
 * 
 * 
 * This source code is part of the Board project, a C++ library whose
 * purpose is to allow simple drawings in EPS, FIG or SVG files.
 * 
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-C
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 * 
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms
 * 
 */
#ifndef _BOARD_BOARD_H_
#define _BOARD_BOARD_H_

#include <ostream>
#include <string>

#include <vector>

#include "Point.h"
#include "Shapes.h"
#include "ShapeList.h"

namespace BoardLib {

/** 
 * The Board class.
 * @brief Class for EPS, FIG or SVG drawings.
 * @version 0.5
 */
class Board : public ShapeList {
  
public:

  /** 
   * Constructs a new board and sets the background color, if any.
   * 
   * @param backgroundColor A color for the drawing's background.
   */
  Board( const Color & backgroundColor = Color::none );

  /** 
   * Copy constructor.
   * 
   * @param other The object to be copied.
   */
  Board( const Board & other );

  ~Board();

  /** 
   * The operator =
   * 
   * @param other The object to be copied.
   * 
   * @return A reference to the left operand.
   */
  Board & operator=( const Board & other );
  
  /** 
   * Clears the board with a given background color.
   * 
   * @param color The board background color (may be Color::none).
   */
  void clear( const Color & color = Color::none );

  /** 
   * Clears the board and set the background color from an RGB triple.
   * 
   * @param red 
   * @param green 
   * @param blue 
   */
  inline void clear( unsigned char red, unsigned char green, unsigned char blue );

  /** 
   * Draws a line from (x1,y1) to (x2,y2).
   * 
   * @param x1 First coordinate of the first extremity.
   * @param y1 Second coordinate of the first extremity.
   * @param x2 First coordinate of the second extremity.
   * @param y2 Second coordinate of the second extremity.
   * @param depth Depth of the line.
   */
  void drawLine( float x1, float y1, float x2, float y2, 
		 int depth = -1 );

  /** 
   * Draws a line from (x1,y1) to (x2,y2) with an arrow at (x2,y2).
   * 
   * @param x1 First coordinate of the first extremity.
   * @param y1 Second coordinate of the first extremity.
   * @param x2 First coordinate of the second extremity.
   * @param y2 Second coordinate of the second extremity.
   * @param filled Whether or not the arrow is filled.
   * @param depth Depth of the line.
   */
  void drawArrow( float x1, float y1, float x2, float y2,
		  bool filled = false,
		  int depth = -1 );

  /** 
   * Draws a triangle.
   * 
   * @param x1 First coordinate of the first vertex.
   * @param y1 Second coordinate of the first vertex.
   * @param x2 First coordinate of the second vertex.
   * @param y3 Second coordinate of the second vertex.
   * @param x3 First coordinate of the third vertex.
   * @param y3 Second coordinate of the third vertex.
   * @param depth Depth of the triangle.
   */
  void drawTriangle( float x1, float y1, 
		     float x2, float y2, 
		     float x3, float y3, 
		     int depth = -1 );

  /** 
   * Draws a triangle.
   * 
   * @param p1 First vertex.
   * @param p2 Second vertex.
   * @param p3 Third vertex.
   * @param depth Depth of the triangle.
   */
  void drawTriangle( const Point & p1,
		     const Point & p2, 
		     const Point & p3, 
		     int depth = -1 );

  /** 
   * Draws a filled triangle.
   * 
   * @param x1 First coordinate of the first vertex.
   * @param y1 Second coordinate of the first vertex.
   * @param x2 First coordinate of the second vertex.
   * @param y3 Second coordinate of the second vertex.
   * @param x3 First coordinate of the third vertex.
   * @param y3 Second coordinate of the third vertex.
   * @param depth Depth of the triangle.
   */
  void fillTriangle( float x1, float y1, 
		     float x2, float y2, 
		     float x3, float y3, 
		     int depth = -1 );

  /** 
   * Draws a triangle with Gouraud-like shaded colors. 
   * 
   * @param p1 
   * @param color1 
   * @param p2 
   * @param color2 
   * @param p3 
   * @param color3 
   * @param divisions number of triangle subdivisions.
   * @param depth The depth of the triangle.
   */
  void fillGouraudTriangle( const Point & p1,
			    const Color & color1,
			    const Point & p2,
			    const Color & color2,
			    const Point & p3,
			    const Color & color3,
			    unsigned char divisions = 3,
			    int depth = -1 );

  /** 
   * Draws a triangle with Gouraud-like shaded colors. 
   * 
   * @param x1 
   * @param y1 
   * @param color1 
   * @param x2 
   * @param y2 
   * @param color2 
   * @param x3 
   * @param y3 
   * @param color3 
   * @param divisions 
   * @param depth 
   */
  inline void fillGouraudTriangle( const float x1, const float y1,
				   const Color & color1,
				   const float x2, const float y2, 
				   const Color & color2,
				   const float x3, const float y3,
				   const Color & color3,
				   unsigned char divisions = 3,
				   int depth = -1 );

  /** 
   * Draws a triangle with a Gouraud-like shaded color according to
   * the current fill color and a brightness value given for each vertex. 
   * @param p1 
   * @param brightness1
   * @param p2 
   * @param brightness2 
   * @param p3 
   * @param brightness3
   * @param divisions number of triangle subdivisions.
   * @param depth The depth of the triangle.
   */
  void fillGouraudTriangle( const Point & p1,
			    const float brightness1,
			    const Point & p2,
			    const float brightness2,
			    const Point & p3,
			    const float brightness3,
			    unsigned char divisions = 3,
			    int depth = -1 );

  /** 
   * Draws a triangle with a Gouraud-like shaded color according to
   * the current fill color and a brightness value given for each vertex. 
   * 
   * @param x1 
   * @param y1 
   * @param brightness1
   * @param x2 
   * @param y2 
   * @param brightness2
   * @param x3 
   * @param y3 
   * @param brightness3
   * @param divisions
   * @param depth 
   */
  inline void fillGouraudTriangle( const float x1, const float y1,
				   const float brightness1,
				   const float x2, const float y2, 
				   const float brightness2,
				   const float x3, const float y3,
				   const float brightness3,
				   unsigned char divisions = 3,
				   int depth = -1 );


  /** 
   * Draws a filled triangle.
   * 
   * @param p1 First vertex.
   * @param p2 Second vertex.
   * @param p3 Third vertex.
   * @param depth Depth of the triangle.
   */
  void fillTriangle( const Point & p1,
		     const Point & p2, 
		     const Point & p3, 
		     int depth = -1 );
  
  /** 
   * Draws a rectangle.
   * 
   * @param x First coordinate of the upper left corner.
   * @param y Second coordinate of the upper left corner.
   * @param width Width of the rectangle.
   * @param height Height of the rectangle.
   * @param depth Depth of the rectangle.
   */
  void drawRectangle( float x, float y, 
		      float width, float height,
		      int depth = -1 );

  /** 
   * Draws a rectangle filled with the current pen color.
   * 
   * @param x First coordinate of the upper left corner.
   * @param y Second coordinate of the upper left corner.
   * @param width Width of the rectangle.
   * @param height Height of the rectangle.
   * @param depth Depth of the rectangle.
   */
  void fillRectangle( float x, float y,
		      float width, float height,
		      int depth = -1 );

  /** 
   * Draws a circle.
   * 
   * @param x First coordinate of the circle's center.
   * @param y Second coordinate of the circle's center.
   * @param radius Radius of the circle.
   * @param depth Depth of the circle.
   */
  void drawCircle( float x, float y, float radius,
		   int depth = -1 );
 
  /** 
   * Draws a circle filled with the current pen color.
   * 
   * @param x First coordinate of the circle's center.
   * @param y Second coordinate of the circle's center.
   * @param radius Radius of the circle.
   * @param depth Depth of the circle.
   */
  void fillCircle( float x, float y, float radius,
		   int depth = -1);

  /** 
   * Draws an ellipse.
   * 
   * @param x First coordinate of the circle's center.
   * @param y Second coordinate of the circle's center.
   * @param radius Radius of the circle.
   * @param depth Depth of the circle.
   */
  void drawEllipse( float x, float y, 
		    float xRadius, float yRadius,
		    int depth = -1);
 
  /** 
   * Draws an ellipse filled with the current pen color.
   * 
   * @param x First coordinate of the circle's center.
   * @param y Second coordinate of the circle's center.
   * @param xRadius X axis radius of the ellipse.
   * @param yRadius Y axis radius of the ellipse.
   * @param depth Depth of the circle.
   */
  void fillEllipse( float x, float y, 
		    float xRadius, float yRadius,
		    int depth = -1);

  /** 
   * Draws a polygonal line.
   * 
   * @param points A vector of points.
   * @param depth The depth of the polyline.
   */
  void drawPolyline( const std::vector<Point> & points,
		     int depth = -1 );
  
  /** 
   * Draws a closed polygonal line.
   * 
   * @param points A vector of points.
   * @param depth The depth of the polyline.
   */
  void drawClosedPolyline( const std::vector<Point> & points,
			   int depth = -1 );

  /** 
   * Draws a filled polygon.
   * 
   * @param points A vector of points.
   * @param depth The depth of the polygon.
   */
  void fillPolyline( const std::vector<Point> & points,
		     int depth = -1 );
    
  /** 
   * Draws a string of text.
   * 
   * @param x The first coordinates of the lower left corner.
   * @param y The second coordinates of the lower left corner.
   * @param text The text. 
   * @param depth The depth of the text.
   */
  void drawText( float x, float y, const char * text, 
		 int depth = -1 );

  /** 
   * Changes the current font and font size.
   *
   * @param font The name of the font.
   * @param fontSize The new font size.
   * @return The board itself.
   */
  Board & setFont( std::string font, float fontSize );
  
  /** 
   * Changes the font size.
   * 
   * @param fontSize The new font size.
   * @return The board itself.
   */
  Board & setFontSize( float fontSize ); 

  /** 
   * Changes the current pen color.
   * 
   * @param red Red component.
   * @param green Green component.
   * @param blue Blue component.
   * @return The board itself.
   */
  Board & setPenColorRGBi( unsigned char red,
			   unsigned char green,
			   unsigned char blue,
			   unsigned char alpha = 255 );

  /** 
   * Changes the current pen color.
   * 
   * @param red Red
   * @param green 
   * @param blue 
   * @param alpha 
   * @return The board itself.
   */  
  Board & setPenColorRGBf(  float red,
			    float green,
			    float blue, 
			    float alpha = 1.0f );

  /** 
   * Changes the current pen color.
   *
   * In order to use no pen, one may set the pen color to Color::none. 
   * @param color The pen color.
   * @return The board itself.
   */
  Board & setPenColor( const Color & color );
  

  /** 
   * Changes the current fill color.
   * 
   * @param red Red component.
   * @param green Green component.
   * @param blue Blue component.
   * @param alpha The opacity. 
   * @return The board itself.
   */
  Board & setFillColorRGBi( unsigned char red,
			    unsigned char green,
			    unsigned char blue,
			    unsigned char alpha = 255 );
  
  /** 
   * Changes the current fill color.
   * 
   * @param red Red component.
   * @param green Green component.
   * @param blue Blue component.
   * @param alpha The opacity.
   * @return The board itself.
   */
  Board & setFillColorRGBf( float red, float green, float blue, float alpha = 1.0f );

  /** 
   * Changes the current fill color.
   * 
   * In order to use no fill color, one may set this color to Color::none. 
   * @param color The fill color.
   * @return The board itself.
   */
  Board & setFillColor( const Color & color );
  
  /** 
   * Changes the current line thickness (1/72 inche unit).
   * 
   * @param width The new line thickness.
   * @return The board itself.
   */
  Board & setLineWidth( float width );
  
  /** 
   * Set the line cap style. 
   * 
   * @param cap The cap-style which can be Shape::ButtCap, 
   * Shape::RoundCap or Shape::SquareCap.
   * 
   * @return The board itself.
   */  
  inline Board & setLineCap( Shape::LineCap cap ); 
 
  /** 
   * Set the line joine style. 
   * 
   * @param cap The join-style which can be Shape::MiterJoin, 
   * Shape::RoundJoin or Shape::BevelJoin.
   * 
   * @return The board itself.
   */  
  inline Board & setLineJoin( Shape::LineJoin join );

  /** 
   * Changes the background color of the whole drawing.
   * 
   * @param color A color (may be Color::none).
   */
  void backgroundColor( const Color & color );

  /** 
   * Draws the current drawing's bounding box as a rectangle.
   * 
   * @param depth The depth of the rectangle.
   */
  void drawBoundingBox( int depth = -1 );

  /** 
   * Save the drawing in an EPS, XFIG of SVG file depending 
   * on the filename extension.
   * 
   * @param filename Path of the file to be created.
   */
  void save( const char * filename ) const; 

  /** 
   * Saves the drawing in an EPS file.
   * 
   * @param filename The EPS file name.
   * @param scale A scale factor to be applied to the while figure before saving.
   */
  void saveEPS( const char * filename, float scale = 1.0f ) const ;

  /** 
   * Saves the drawing in an XFig file.
   * 
   * @param filename The name of the FIG file.
   * @param scale A scale factor to be applied to the while figure before saving.
   */
  void saveFIG( const char * filename, float scale = 1.0f ) const;

  /** 
   * Save the drawing in an SVG file.
   * 
   * @param filename The name of the file.
   * @param scale A scale factor to be applied to the while figure before saving.
   */
  void saveSVG( const char * filename, float scale = 1.0f ) const;
  
 protected:

  struct State {
    Color penColor;		/**< The pen color. */
    Color fillColor;		/**< The fill color. */
    float lineWidth;		/**< The line thickness. */
    Shape::LineCap lineCap;	/**< The type of line extremities. */
    Shape::LineJoin lineJoin;	/**< The type of line junction. */
    std::string font;		/**< The font. */
    float fontSize;		/**< The font size. */
    State();
  };
  
  State _state;			 /**< The current state. */
  // std::vector< Shape* > _shapes; /**< Vector of the shapes. */
  Color _backgroundColor;	 /**< The color of the background. */
};

extern const char * XFigPostscriptFontnames[];

inline void
Board::clear( unsigned char red, unsigned char green, unsigned char blue )
{
  clear( Color( red, green, blue ) );
}

inline Board &
Board::setLineCap( Shape::LineCap cap )
{
  _state.lineCap = cap;
  return *this;
}
  
inline Board &
Board::setLineJoin( Shape::LineJoin join )
{
  _state.lineJoin = join;
  return *this;
}

inline void
Board::fillGouraudTriangle( const float x1, const float y1,
			    const Color & color1,
			    const float x2, const float y2, 
			    const Color & color2,
			    const float x3, const float y3,
			    const Color & color3,
			    unsigned char divisions,
			    int depth /* = -1 */ )
{
  fillGouraudTriangle( Point( x1, y1 ), color1,
		       Point( x2, y2 ), color2,
		       Point( x3, y3 ), color3,
		       divisions, depth );		       
}

void
Board::fillGouraudTriangle( const float x1, const float y1,
			    const float brightness1,
			    const float x2, const float y2, 
			    const float brightness2,
			    const float x3, const float y3,
			    const float brightness3,
			    unsigned char divisions,
			    int depth /* = -1 */ )
{
  fillGouraudTriangle( Point( x1, y1 ), brightness1,
		       Point( x2, y2 ), brightness2,
		       Point( x3, y3 ), brightness3,
		       divisions, depth );
}

} // namespace Board

#endif
