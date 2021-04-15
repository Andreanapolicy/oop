#include "CController.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "common_libs.h"

CController::CController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({ { "rectangle", [this](const std::string& args) { return GetRectangle(args); } },
		  { "line", [this](const std::string& args) { return GetLine(args); } },
		  { "circle", [this](const std::string& args) { return GetCircle(args); } },
		  { "triangle", [this](const std::string& args) { return GetTriangle(args); } },
		})
{
}

void CController::GetShape()
{
	std::string commandLine;
	std::getline(m_input, commandLine);

	std::istringstream stream(commandLine);

	std::string action;
	std::string args;
	std::getline(stream, action, ' ');
	args = std::getline(stream, args) ? args : "";

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(args);
	}
}

void CController::WriteAllInfoAboutShapes() const
{
	for (const auto element : m_shapesList)
	{
		m_output << element.ToString() << std::endl;
	}
}

void CController::GetRectangle(const std::string& args)
{
	std::string commandLine;

	std::istringstream stream(args);

	double topPointX;
	stream >> topPointX;
	double topPointY;
	stream >> topPointY;
	double width;
	stream >> width;
	double height;
	stream >> height;

	std::string outlineColor;
	stream >> outlineColor;
	std::string fillColor;
	stream >> fillColor;


	CPoint topLeftPoint(topPointX, topPointY);

	CRectangle rectangle(topLeftPoint, width, height, ParseColor(outlineColor), ParseColor(fillColor));
		
	m_shapesList.push_back(rectangle);
}

void CController::GetTriangle(const std::string& args)
{
	std::string commandLine;

	std::istringstream stream(args);

	double firstVertexX;
	stream >> firstVertexX;
	double firstVertexY;
	stream >> firstVertexY;

	double secondVertexX;
	stream >> secondVertexX;
	double secondVertexY;
	stream >> secondVertexY;

	double thirdVertexX;
	stream >> thirdVertexX;
	double thirdVertexY;
	stream >> thirdVertexY;

	std::string outlineColor;
	stream >> outlineColor;
	std::string fillColor;
	stream >> fillColor;

	CPoint firstVertex(firstVertexX, firstVertexY);
	CPoint secondVertex(secondVertexX, secondVertexY);
	CPoint thirdVertex(thirdVertexX, thirdVertexY);

	CTriangle triangle(firstVertex, secondVertex, thirdVertex, ParseColor(outlineColor), ParseColor(fillColor));

	m_shapesList.push_back(triangle);
}

void CController::GetCircle(const std::string& args)
{
	std::string commandLine;

	std::istringstream stream(args);

	double centralPointX;
	stream >> centralPointX;
	double centralPointY;
	stream >> centralPointY;
	double radius;
	stream >> radius;

	std::string outlineColor;
	stream >> outlineColor;
	std::string fillColor;
	stream >> fillColor;

	CPoint centralPoint(centralPointX, centralPointY);

	CCircle circle(centralPoint, radius, ParseColor(outlineColor), ParseColor(fillColor));

	m_shapesList.push_back(circle);
}

void CController::GetLine(const std::string& args)
{
	std::string commandLine;

	std::istringstream stream(args);

	double firstPointX;
	stream >> firstPointX;
	double firstPointY;
	stream >> firstPointY;

	double secondPointX;
	stream >> secondPointX;
	double secondPointY;
	stream >> secondPointY;

	std::string outlineColor;
	stream >> outlineColor;
	
	CPoint firstPoint(firstPointX, firstPointY);
	CPoint secondPoint(secondPointX, secondPointY);

	CLineSegment line(firstPoint, secondPoint, ParseColor(outlineColor));

	m_shapesList.push_back(line);
}

uint32_t CController::ParseColor(const std::string& color)
{
	auto colorRgb = static_cast<uint32_t>(stoul(color, nullptr, 16) << 8);
	uint32_t colorRgbOpaque = colorRgb | 0x000000FF;

	return colorRgbOpaque;
}