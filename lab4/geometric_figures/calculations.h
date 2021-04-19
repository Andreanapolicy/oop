#pragma once
#include "common_libs.h";
#include "IShape.h";


const std::unique_ptr<IShape>& GetShapeWithMaxArea();
const std::unique_ptr<IShape>& GetShapeWithMinPerimeter();