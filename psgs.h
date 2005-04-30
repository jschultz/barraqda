//
// ghostscript_interface
//
// Part of KDVI - A framework for multipage text/gfx viewers
//
// (C) 2004 Stefan Kebekus
// Distributed under the GPL

#ifndef _PSGS_H_
#define _PSGS_H_


#include <ktempfile.h>
#include <qstring.h>
#include <qintdict.h>

#include "../kviewshell/pageNumber.h"


class QPainter;

class pageInfo
{
public:
  pageInfo(QString _PostScriptString);
  ~pageInfo();

  QColor    background;
  QColor    permanentBackground;
  QString   *PostScriptString;
};


class ghostscript_interface  : public QObject 
{
 Q_OBJECT

public:
  ghostscript_interface();
  ~ghostscript_interface();

  void clear();

  // sets the PostScript which is used on a certain page
  void setPostScript(PageNumber page, QString PostScript);

  // sets path from additional postscript files may be read
  void setIncludePath(const QString &_includePath);

  // Sets the background color for a certain page. If permanent is false then the original 
  // background color can be restored by calling restoreBackground(page).
  // The Option permanent = false is used when we want to display a different paper 
  // color as the one specified in the dvi file.
  void setBackgroundColor(PageNumber page, QColor background_color, bool permanent = true);

  // Restore the background to the color which was specified by the last call to setBackgroundColor()
  // With option permanent = true.
  void restoreBackgroundColor(PageNumber page);

  // Draws the graphics of the page into the painter, if possible. If
  // the page does not contain any graphics, nothing happens
  void     graphics(PageNumber page, double dpi, long magnification, QPainter *paint );

  // Returns the background color for a certain page. If no color was
  // set, Qt::white is returned.
  QColor   getBackgroundColor(PageNumber page);

  QString  *PostScriptHeaderString;

  /** This method tries to find the PostScript file 'filename' in the
   DVI file's directory, and, if that fails, uses kpsewhich to find
   the file. If the file is found, the full path (including file name)
   is returned. Otherwise, the method returns the first
   argument. TODO: use the DVI file's baseURL, once this is
   implemented.
  */
  static  QString locateEPSfile(const QString &filename, class dvifile *dvi);

private:
  void                  gs_generate_graphics_file(PageNumber page, const QString &filename, long magnification);
  QIntDict<pageInfo>    pageList;

  double                resolution;   // in dots per inch
  int                   pixel_page_w; // in pixels
  int                   pixel_page_h; // in pixels

  QString               includePath;

  // Output device that ghostscript is supposed tp use. Default is
  // "png256". If that does not work, gs_generate_graphics_file will
  // automatically try other known device drivers. If no known output
  // device can be found, something is badly wrong. In that case,
  // "gsDevice" is set to an empty string, and
  // gs_generate_graphics_file will return immediately.
  QValueListIterator<QString> gsDevice;

  // A list of known devices, set by the constructor. This includes
  // "png256", "pnm". If a device is found to not work, its name is
  // removed from the list, and another device name is tried.
  QStringList           knownDevices;

signals:
  /** Passed through to the top-level kpart. */
  void setStatusBarText( const QString& );
};

#endif
