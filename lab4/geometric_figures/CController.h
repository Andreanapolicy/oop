#pragma once
#include "common_libs.h"
#include "IShape.h"

class CController
{
public:
	CController(std::istream& input, std::ostream& output);
	void GetShape();
	void WriteAllInfoAboutShapes() const;

	void GetRectangle(const std::string& args);
	void GetLine(const std::string& args);
	void GetTriangle(const std::string& args);
	void GetCircle(const std::string& args);
	void GetHelp(const std::string& args);

private:
	uint32_t ParseColor(const std::string& color);
	const std::unique_ptr<IShape>& GetShapeWithMaxArea() const;
	const std::unique_ptr<IShape>& GetShapeWithMinPerimeter() const;

	using ShapesList = std::vector<std::unique_ptr<IShape>>;
	using Handler = std::function<void(const std::string& args)>;
	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	std::ostream& m_output;
	ShapesList m_shapesList;

	
	const ActionMap m_actionMap;
};
