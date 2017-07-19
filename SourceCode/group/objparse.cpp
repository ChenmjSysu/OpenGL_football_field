#include "objparse.h"

//��ȡ���ÿ������������ֵ
void get_index(char str[], int &v, int &t, int &n);

ObjParse::ObjParse() {}

//����ĳ��obj�ļ�
void ObjParse::parse(char* filename) {
    FILE* fp;
	fp = fopen(filename, "r");
	//���ļ�ʧ��
	if(fp == 0) {
	    printf("Error while open file  %s \n", filename);
	}
	
	char label[20], next[20];
	float xx, yy, zz;
	int index0, index1, index2;
	while(fscanf(fp, "%s", label) != EOF) {
		if(strcmp(label, "v") == 0) {
			fscanf(fp, "%f %f %f", &xx, &yy, &zz);
			vertices.push_back(Vertex(xx, yy, zz));
		}
		else if(strcmp(label, "vt") == 0) {
			fscanf(fp, "%f %f %f", &xx, &yy, &zz);
			textures.push_back(Vertex(xx, yy, zz));
		}
		else if(strcmp(label, "vn") == 0) {
			fscanf(fp, "%f %f %f", &xx, &yy, &zz);
			normals.push_back(Vertex(xx, yy, zz));
		}
		else if(strcmp(label, "f") == 0) {
			Face f;
			fscanf(fp, "%s", next);
			//��һ��Ҳ������
			while(next[0] >= '0' && next[0] <= '9') {
				int v(0), t(0), n(0);
				get_index(next, v, t, n);
				f.vertex_index.push_back(v);
				f.texture_index.push_back(t);
				f.normal_index.push_back(n);
				if(fscanf(fp, "%s", next) == EOF) {break;}
			}
			//���ݵõ���next��ʹ�ļ�ָ�����
			for(int j = 0; next[j] != '\0'; j++) {
			    fseek(fp, -1, 1);
			}
			faces.push_back(f);
		}
		else if(strcmp(label, "usemtl") == 0) {}
		else if(strcmp(label, "mtllib") == 0) {}
	}
	fclose(fp);
}

//����ͼ��
void ObjParse::draw() {
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	std::vector<Face>::iterator face_it = faces.begin();
	for(; face_it != faces.end(); face_it++) {
		//���ݶ������ÿ����
		glBegin(GL_LINE_LOOP);
		for(int i = 0; i < face_it->vertex_index.size(); i++) {
			int v_index = face_it->vertex_index[i] - 1;  //���������
			glVertex3f(vertices[v_index].x, vertices[v_index].y, vertices[v_index].z);
		}
		glEnd();
	}
}

//��ȡ���ÿ������������ֵ
void get_index(char str[], int &v, int &t, int &n) {
    char index_char[10];
	int index_count = 0;
	int j = 0;
	for(int i = 0; str[i] != '\0'; i++) {
		if(str[i] >= '0' && str[i] <= '9') {			
			index_char[j++] = str[i];
		}
		else {
		    index_char[j] = '\0';
			if(index_count == 0) v = atoi(index_char);
			if(index_count == 1) t = atoi(index_char);
			if(index_count == 2) n = atoi(index_char);
			index_count++;
			j = 0;
		}
	}
	index_char[j] = '\0';
	if(index_count == 0) v = atoi(index_char);
	if(index_count == 1) t = atoi(index_char);
	if(index_count == 2) n = atoi(index_char);
}