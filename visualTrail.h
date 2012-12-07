#ifndef VISUAL_TRAIL_H
#define VISUAL_TRAIL_H

#include <osgUtil/Optimizer>
//#include <osgDB/ReadFile>

//#include <osgDB/FileUtils>
//#include <osgProducer/Viewer>
//#include <osgGA/MatrixManipulator>
//#include <osgGA/FlightManipulator>
#include <osgGA/GUIEventHandler>
#include <osg/ShapeDrawable>

#include <osg/PolygonMode>
#include <osgSim/SphereSegment>

#include <osg/Material>
#include <osg/Geode>
#include <osg/BlendFunc>
#include <osg/Depth>

#include <osg/Projection>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/LineWidth>

#include <osgText/Text>


class setToAbsoluteTransform : public osg::MatrixTransform
{
public:
	
	class setToAbsoluteCoordsCallback : public osg::NodeCallback
	{
	public:
		setToAbsoluteCoordsCallback() {};
		virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
		{
			setToAbsoluteTransform * absXform = dynamic_cast<setToAbsoluteTransform*> (node );
			if(absXform != NULL)
			{
				osg::NodePath& np = nv->getNodePath();
				np.pop_back();
				absXform->setMatrix(osg::Matrix::inverse(osg::computeLocalToWorld(np )));
			}
			traverse(node, nv);
		}
	};
	setToAbsoluteTransform()
	{
		setUpdateCallback(new setToAbsoluteCoordsCallback() );
	}
protected:
};

class visualTrail : public osg::Group
{
public:
	int getLength() { return vtVerts->size(); }
	visualTrail(double width = 2.0);
	void setWidth( double w) { halfWidth = w/2.0;}
	void addPoint( osg::Vec3 pt);
	void addPoint(osg::Matrixd m);
	void addPoint( double x, double y, double z);
	static osg::StateSet* initVTState();
protected:
	osg::Vec3d* startPoint;
	osg::Geode* vtGeode;
	setToAbsoluteTransform* absXForm;
	double halfWidth;
	osg::Box* startPointBox;
	osg::Geometry* vtGeometry;
	osg::Vec3Array* vtVerts;
	osg::DrawElementsUInt* vtPrimitive;
	int numPoints;
	static osg::StateSet* vtStateSet;
};
#endif