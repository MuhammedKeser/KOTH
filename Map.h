#pragma once

class Map
{
public:
	//Singleton Instance
	Map* CreateMap(int height, int width) { m_map = Map(height, width); }
	static Map m_map;
	
//Members and ctor
protected:
	int ** m_grid;
	int m_width, m_height;
	Map(int height, int width	) :m_width(width), m_height(height) {};

//Methods
public:
	static void SetGrid(int ** grid) { m_map.m_grid = grid; }
	static void SetGridCell(int xIndex, int yIndex, int value) { m_map.m_grid[xIndex][yIndex] = value; }
	static const int& GetGridCell(int xIndex, int yIndex) { return m_map.m_grid[xIndex][yIndex]; }
	static const int& GetHeight() { return m_map.m_height; }

};