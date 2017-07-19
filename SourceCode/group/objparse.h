#ifndef __OBJPARSE__H__
#define __OBJPARSE__H__

#include <stdio.h>
#include <vector>

#include <gl/glut.h>

//顶点结构
struct Vertex {
    float x;
	float y;
	float z;
	//构造函数
	Vertex(float x_ = 0, float y_ = 0, float z_ = 0): x(x_), y(y_), z(z_) {}
};

//面
struct Face {
	std::vector<int> vertex_index;
	std::vector<int> texture_index;
	std::vector<int> normal_index;
};

//解析obj文件的类
class ObjParse {
public:
	ObjParse();
	ObjParse(char* filename);
	void parse(char* filename);
	void draw();
	int getVerticesNumber();
	int getTexturesNumber();
	int getNormalsNumber();
private:
	std::vector<Vertex> vertices;
	std::vector<Vertex> textures;
	std::vector<Vertex> normals;

	std::vector<Face> faces;
};

#endif //__OBJPARSE__H__