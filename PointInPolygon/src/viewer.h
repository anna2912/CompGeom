#include "visualization/viewer_adapter.h"
#include "visualization/draw_util.h"

#include "io/point.h"

#include "PointInPolygon.h"

using namespace visualization;
using geom::structures::point_type;
using geom::structures::contour_type;

struct point_in_poly_viewer : viewer_adapter
{
    point_in_poly_viewer()
        : wait4pt(true)
        , wait4answer(true)
    {}

    void draw(drawer_type & drawer)     const;
    void print(printer_type & printer)  const;

    bool on_double_click(point_type const & pt);
    bool on_key(int key);

private:
    std::vector<point_type>         pts_; 
    point_type pt2check;
    bool wait4pt;
    bool answerBinary;
    bool answerCrossing;
    bool wait4answer;
};

void point_in_poly_viewer::draw(drawer_type & drawer) const
{
    drawer.set_color(Qt::blue);
    for (point_type const & pt : pts_){
        drawer.draw_point(pt, 3);
    }

    drawer.set_color(Qt::red);
    for (int i = 0; i < pts_.size(); i++){
        point_type const &pt1 = pts_[i];
        point_type const &pt2 = pts_[(i+1)%pts_.size()];
        drawer.draw_line(pt1, pt2, 2);
    }

    drawer.set_color(Qt::green);
    if (!wait4pt)
        drawer.draw_point(pt2check, 3);

}

void point_in_poly_viewer::print(printer_type & printer) const
{
    printer.corner_stream() << "Put vertices of polygon in counterclockwise order. When finished, press \"i\"." << endl;
    printer.corner_stream() << "Double-click to put the point to check. Press \"enter\"." << endl;
    if(!wait4answer){
        printer.corner_stream() << "Binary search (convex polygons only): ";
        if(answerBinary)
            printer.corner_stream() << "in polygon" << endl;
        else
            printer.corner_stream() << "out of polygon" << endl;

        printer.corner_stream() << "Crossings number: ";
        if(answerCrossing)
            printer.corner_stream() << "in polygon" << endl;
        else
            printer.corner_stream() << "out of polygon" << endl;
    }

}

bool point_in_poly_viewer::on_double_click(point_type const & pt)
{
    if(wait4pt) {
        pts_.push_back(pt);
    }
    else {
        pt2check = pt;
        wait4answer = true;
    }
    return true;
}

bool point_in_poly_viewer::on_key(int key)
{
    switch (key)
    {
    case Qt::Key_Return: 
        if (pts_.size() >= 3 && !wait4pt)
        {
            answerBinary = geom::algorithms::point_in_poly::BinarySearch(pts_, pt2check);
            answerCrossing = geom::algorithms::point_in_poly::CrossingNumber(pts_, pt2check);
            wait4answer = false;
            return true;
        }
        break;
    case Qt::Key_I:
        {
            wait4pt = false;
        }
        break;
    case Qt::Key_S:
        {
            std::string filename = QFileDialog::getSaveFileName(
                get_wnd(), 
                "Save Points"
            ).toStdString();
            if (filename != "")
            {
                std::ofstream out(filename.c_str());
                boost::copy(pts_, std::ostream_iterator<point_type>(out, "\n"));
            }
        }
        break;
    case Qt::Key_L:
        {
            std::string filename = QFileDialog::getOpenFileName(
                get_wnd(), 
                "Load Points"
            ).toStdString();
            if (filename != "")
            {
                std::ifstream in(filename.c_str());
                std::istream_iterator<point_type> beg(in), end;
                pts_.assign(beg, end);
                return true;
            }
        }
    }
    return false;
}
