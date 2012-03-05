#include "stdafx.h"

#include "viewer.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    point_in_poly_viewer viewer;
    visualization::run_viewer(&viewer, "Point in polygon");
}
