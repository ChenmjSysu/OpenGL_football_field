#ifndef __OBJPARSE__H__
#define __OBJPARSE__H__

#include <stdio.h>
#include <vector>

#include <gl/glut.h>

//����ṹ
struct Vertex {
    float x;
	float y;
	float z;
	//���캯��
	Vertex(float x_ = 0, float y_ = 0, float z_ = 0): x(x_), y(y_), z(z_) {}
};

//��
struct Face {
	std::vector<int> vertex_index;
	std::vector<int> texture_index;
	std::vector<int> normal_index;
};

//����obj�ļ�����
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