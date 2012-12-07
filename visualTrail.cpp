#include "visualTrail.h"
#include <iostream>

osg::StateSet* visualTrail::vtStateSet = initVTState();

osg::StateSet* visualTrail::initVTState()
{
	osg::StateSet* svss = new osg::StateSet();
	osg::PolygonMode* polymode = new osg::PolygonMode;
	polymode->setMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE);
	svss->setAttributeAndModes(polymode,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
	osg::LineWidth *lineWidth = new osg::LineWidth; 
	lineWidth->setWidth(2.0f); 
	svss->setAttribute(lineWidth); 
	svss->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	return svss;
}

visualTrail::visualTrail(double width) 
{ 
	vtGeode = new osg::Geode();
	absXForm = new setToAbsoluteTransform();
	numPoints = 0;
	halfWidth = width/2.0;
	vtGeode->setStateSet(vtStateSet);
	vtGeometry = new osg::Geometry();
	vtGeode->addDrawable(vtGeometry);
	vtGeometry->setUseDisplayList(false);
	vtVerts = new osg::Vec3Array;
	vtGeometry->setVertexArray( vtVerts );
	vtPrimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0);
	vtGeometry->addPrimitiveSet(vtPrimitive);
	if(absXForm == NULL){
		std::cout << "Whoa!" << std::endl;
	}
	std::cout << "1" << std::endl;
	this->addChild( (osg::Node*) absXForm );
	std::cout << "2" << std::endl;
	absXForm->addChild( vtGeode );
	std::cout << "3" << std::endl;
}

void visualTrail::addPoint(osg::Vec3 pt)
{
	vtVerts->push_back( pt );
	vtPrimitive->push_back(numPoints);
	numPoints++;
}

void visualTrail::addPoint(osg::Matrixd m)
{
	osg::Vec3d  pt1 = osg::Vec3d(halfWidth,0,0) * m;
	osg::Vec3d  pt2 = osg::Vec3d(-halfWidth,0,0) * m;
	addPoint(pt1);
	addPoint(pt2);
}