#pragma once
#include <iostream>

class Map
{
public:
	//Singleton Instance
	static void CreateMap(int height, int width) { m_map = Map(height, width); ProceduralGeneration(); }
	static void ProceduralGeneration();
	static Map m_map;
	
//Members and ctor
protected:
	int ** m_grid;
	int m_width, m_height;
	Map(int height, int width) :m_width(width), m_height(height) { m_grid = (int**)calloc(height, sizeof(int*)); };

//Methods
public:
	static void SetGrid(int ** grid) { m_map.m_grid = grid; }
	static void SetGridCell(int xIndex, int yIndex, int value) { m_map.m_grid[xIndex][yIndex] = value; }
	static const int& GetGridCell(int xIndex, int yIndex) { return m_map.m_grid[xIndex][yIndex]; }
	static const int& GetHeight() { return m_map.m_height; }
	static const int& GetWidth() { return m_map.m_width; }

};