#include "glGeometryObject.h"

using namespace std;

GL_GEOMETRY_OBJECT::GL_GEOMETRY_OBJECT()
{
	ObjDiv = 60;
	
	Edges = 1;
	EdgesWidth = 1.f;
	ColorIndex2RGB(0, EdgeRcolor, EdgeGcolor, EdgeBcolor);

	Surfaces = 1;
	PointSize = 8.0f;
	ColorIndex2RGB(4, ObjRcolor, ObjGcolor, ObjBcolor);
	ColorAlfaValue(1.f, ObjAlfa);

	CS = 0;
	CSsize = 0.2f,
	CSpointSize = 5.0f;
}

int GL_GEOMETRY_OBJECT::RotationMatrix()
{
	if(0 != CheckData(0))
		return CheckData(0);

	CoordinateSystems();

	RotMat.GetFrom(is.x, is.y, is.z,
               	   js.x, js.y, js.z,
                   ks.x, ks.y, ks.z);
	return 0;
}

void GL_GEOMETRY_OBJECT::SetEdgesColor(unsigned int c)
{
	ColorIndex2RGB(c, EdgeRcolor, EdgeGcolor, EdgeBcolor);
}

void GL_GEOMETRY_OBJECT::SetSurfacesColor(unsigned int c, float Alfa)
{
	ColorIndex2RGB(c, ObjRcolor, ObjGcolor, ObjBcolor);
	ColorAlfaValue(Alfa, ObjAlfa);
}

void GL_GEOMETRY_OBJECT::SetResolution(unsigned int v)
{
	ObjDiv = v;
	ddiv = 360./ObjDiv;
}

void GL_GEOMETRY_OBJECT::DrawObject()
{
	switch(Type)
	{
	    case M_POINT       : Draw_M_POINT(); 	break;
	    case DISC          : Draw_DISC(); 		break;
	    case SPHERE        : Draw_SPHERE(); 	break;
	    case CUBOID        : Draw_CUBOID(); 	break;
	    case CYLINDER      : Draw_CYLINDER(); 	break;
	    case TUBE          : Draw_TUBE(); 		break;
	    case CONE          : Draw_CONE(); 		break;
	}
    
	if(CS)
    	DrawObjCS();
}

void GL_GEOMETRY_OBJECT::DrawObjCS()
{
   	glPointSize(CSpointSize);
   	glBegin (GL_POINTS);
        glColor3f(0.0, 1.0, 0.0);
   		glVertex3f (Base.x, Base.y, Base.z);            
   	glEnd ();

	glBegin (GL_LINES);
	    glColor3f(0.0, 0.0, 1.0);
		glVertex3f (Base.x, Base.y, Base.z);
        glVertex3f (Base.x + Tip.x*CSsize, Base.y + Tip.y*CSsize, Base.z + Tip.z*CSsize);
        glColor3f(1.0, 0.0, 0.0);
		glVertex3f (Base.x, Base.y, Base.z);
        glVertex3f (Base.x + Side.x*CSsize, Base.y + Side.y*CSsize, Base.z + Side.z*CSsize);
	glEnd ();
};

void GL_GEOMETRY_OBJECT::Draw_M_POINT()
{
	glPointSize(PointSize);
	glBegin (GL_POINTS);
		glColor4ub(ObjRcolor, ObjGcolor, ObjBcolor, ObjAlfa);
		glVertex3f (Base.x, Base.y, Base.z);            
	glEnd ();
};

void GL_GEOMETRY_OBJECT::Draw_DISC()
{
	ddiv = 360./ObjDiv;
	
	if(Surfaces)
	{
		glColor4ub(ObjRcolor, ObjGcolor, ObjBcolor, ObjAlfa);

		glDisable( GL_CULL_FACE );

		glBegin (GL_POLYGON);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, R, R, 0);

		glEnd ();
	
		glEnable( GL_CULL_FACE ); // Always back on ?!?
	}
	
	if(Edges)
	{
		glLineWidth(EdgesWidth);
		glColor3ub(EdgeRcolor, EdgeGcolor, EdgeBcolor);

		glBegin (GL_LINE_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, R, R, 0);

		glEnd ();
	}
}

void GL_GEOMETRY_OBJECT::Draw_SPHERE()
{
	ddiv = 360./ObjDiv;
	
	if(Surfaces)
	{
		glColor4ub(ObjRcolor, ObjGcolor, ObjBcolor, ObjAlfa);

		// --- local h, r ---

		vector <float> loc_r;
		vector <float> loc_h;

		for(unsigned int i=1; i<int(0.5*ObjDiv); i++)
		{
			loc_r.push_back(R*cos(-0.5*M_PI + i*ddiv*M_PI/180));
			loc_h.push_back(R*sin(-0.5*M_PI + i*ddiv*M_PI/180));
		}
	
		// --- Base ---
	
		glBegin (GL_TRIANGLE_FAN);
	
			v_pos.GetFrom(0.f, 0.f, -R);
			v_pos = v_pos*RotMat; 
			v_pos += Base; 
			glVertex3f (v_pos.x, v_pos.y, v_pos.z);            
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, loc_r[0], loc_r[0], loc_h[0]);

		glEnd ();

		// --- Side ---
	
		for(unsigned int h=0; h<loc_h.size()-1; h++)
		{
			glBegin (GL_QUAD_STRIP);
	
				for(unsigned int i=0; i<=ObjDiv; i++)
				{
					CirclePoints(i, loc_r[h], loc_r[h], loc_h[h]);
					CirclePoints(i, loc_r[h+1], loc_r[h+1], loc_h[h+1]);
				}
	
			glEnd ();
		}

		// --- Top ---
	
		glBegin (GL_TRIANGLE_FAN);
	
			v_pos.GetFrom(0.f, 0.f, R);
			v_pos = v_pos*RotMat; 
			v_pos += Base; 
			glVertex3f (v_pos.x, v_pos.y, v_pos.z);            
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, loc_r[loc_h.size()-1], -loc_r[loc_h.size()-1], loc_h[loc_h.size()-1]);

		glEnd ();
	}
}

void GL_GEOMETRY_OBJECT::Draw_CUBOID()
{
	if(Surfaces)
	{
		glColor4ub(ObjRcolor, ObjGcolor, ObjBcolor, ObjAlfa);

		// --- Base ---
	
		glBegin (GL_POLYGON);
	
            TransformVertex(-0.5*a, 0.5*b, 0.0);
            TransformVertex(-0.5*a, -0.5*b, 0.0);
            TransformVertex(0.5*a, -0.5*b, 0.0);
            TransformVertex(0.5*a, 0.5*b, 0.0);
            
		glEnd ();
	
		// --- Top ---
	
		glBegin (GL_POLYGON);
	
			TransformVertex( 0.5*a,  0.5*b, c);            
			TransformVertex( 0.5*a, -0.5*b, c);            
			TransformVertex(-0.5*a, -0.5*b, c);            
			TransformVertex(-0.5*a,  0.5*b, c);            

		glEnd ();

		// --- Side ---
	 
		glBegin (GL_QUAD_STRIP);
	
			TransformVertex(-0.5*a,  0.5*b, 0.0f);            
			TransformVertex(-0.5*a,  0.5*b, c);            
			TransformVertex(-0.5*a, -0.5*b, 0.0f);            
			TransformVertex(-0.5*a, -0.5*b, c);            
			TransformVertex( 0.5*a, -0.5*b, 0.0f);            
			TransformVertex( 0.5*a, -0.5*b, c);            
			TransformVertex( 0.5*a,  0.5*b, 0.0f);            
			TransformVertex( 0.5*a,  0.5*b, c);            
			TransformVertex(-0.5*a,  0.5*b, 0.0f);            
			TransformVertex(-0.5*a,  0.5*b, c);            
		
		glEnd ();
	}

	if(Edges)
	{
		glLineWidth(EdgesWidth);
		glColor3ub(EdgeRcolor, EdgeGcolor, EdgeBcolor);

		// --- Base ---

		glBegin (GL_LINE_STRIP);
	
			TransformVertex(-0.5*a,  0.5*b, 0.0f);            
			TransformVertex(-0.5*a, -0.5*b, 0.0f);            
			TransformVertex( 0.5*a, -0.5*b, 0.0f);            
			TransformVertex( 0.5*a,  0.5*b, 0.0f);            
			TransformVertex(-0.5*a,  0.5*b, 0.0f);            

		glEnd ();
		
		// --- Top ---
		
		glBegin (GL_LINE_STRIP);
	
			TransformVertex( 0.5*a,  0.5*b, c);            
			TransformVertex( 0.5*a, -0.5*b, c);            
			TransformVertex(-0.5*a, -0.5*b, c);            
			TransformVertex(-0.5*a,  0.5*b, c);            
			TransformVertex( 0.5*a,  0.5*b, c);            

		glEnd ();
		
		// --- Sides ---
		
		glBegin (GL_LINES);
	
			TransformVertex( 0.5*a,  0.5*b, 0.0f);            
			TransformVertex( 0.5*a,  0.5*b, c);            
			TransformVertex( 0.5*a, -0.5*b, 0.0f);            
			TransformVertex( 0.5*a, -0.5*b, c);            
			TransformVertex(-0.5*a, -0.5*b, 0.0f);            
			TransformVertex(-0.5*a, -0.5*b, c);            
			TransformVertex(-0.5*a,  0.5*b, 0.0f);            
			TransformVertex(-0.5*a,  0.5*b, c);            

		glEnd ();
	}
}

void GL_GEOMETRY_OBJECT::Draw_CYLINDER()
{
	ddiv = 360./ObjDiv;
	
	if(Surfaces)
	{
		glColor4ub(ObjRcolor, ObjGcolor, ObjBcolor, ObjAlfa);

		// --- Base ---
	
		glBegin (GL_POLYGON);
	
			for(unsigned int i=0; i<ObjDiv; i++)
				CirclePoints(i, R, R, 0);

		glEnd ();
	
		// --- Top ---
	
		glBegin (GL_POLYGON);
	
			for(unsigned int i=0; i<ObjDiv; i++)
				CirclePoints(i, R, -R, H);

		glEnd ();

		// --- Side ---
	 
		glBegin (GL_QUAD_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
			{
				CirclePoints(i, R, R, 0);
				CirclePoints(i, R, R, H);
			}

		glEnd ();
	}

	if(Edges)
	{
		glLineWidth(EdgesWidth);
		glColor3ub(EdgeRcolor, EdgeGcolor, EdgeBcolor);

		// --- Base ---

		glBegin (GL_LINE_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, R, R, 0);

		glEnd ();
		
		// --- Top ---
		
		glBegin (GL_LINE_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, R, R, H);

		glEnd ();
	}
}

void GL_GEOMETRY_OBJECT::Draw_TUBE()
{
	ddiv = 360./ObjDiv;
	
	if(Surfaces)
	{
		glColor4ub(ObjRcolor, ObjGcolor, ObjBcolor, ObjAlfa);

		// --- Base ---
	
		glBegin (GL_QUAD_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
			{
				CirclePoints(i, r, r, 0);
				CirclePoints(i, R, R, 0);
			}

		glEnd ();
	
		// --- Top ---
	
		glBegin (GL_QUAD_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
			{
				CirclePoints(i, r, -r, H);
				CirclePoints(i, R, -R, H);
			}

		glEnd ();

		// --- Side ---
	 
		glBegin (GL_QUAD_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
			{
				CirclePoints(i, R, R, 0);
				CirclePoints(i, R, R, H);
			}

		glEnd ();
	
		glBegin (GL_QUAD_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
			{
				CirclePoints(i, r, r, H);
				CirclePoints(i, r, r, 0);
			}

		glEnd ();
	}

	if(Edges)
	{
		glLineWidth(EdgesWidth);
		glColor3ub(EdgeRcolor, EdgeGcolor, EdgeBcolor);

		// --- Base ---

		glBegin (GL_LINE_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, R, R, 0);

		glEnd ();
		
		glBegin (GL_LINE_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, r, r, 0);

		glEnd ();

		// --- Top ---
		
		glBegin (GL_LINE_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, R, R, H);

		glEnd ();
		
		glBegin (GL_LINE_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, r, r, H);

		glEnd ();
	}
}

void GL_GEOMETRY_OBJECT::Draw_CONE()
{
	ddiv = 360./ObjDiv;
	
	if(Surfaces)
	{
		glColor4ub(ObjRcolor, ObjGcolor, ObjBcolor, ObjAlfa);

		// --- Base ---
	
		glBegin (GL_POLYGON);
	
			for(unsigned int i=0; i<ObjDiv; i++)
				CirclePoints(i, R, R, 0);

		glEnd ();
	
		// --- Cone ---
	 
		glBegin (GL_TRIANGLE_FAN);
	
			v_pos.GetFrom(0.f, 0.f, H);
			v_pos = v_pos*RotMat; 
			v_pos += Base; 
			glVertex3f (v_pos.x, v_pos.y, v_pos.z);            
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, R, -R, 0);

		glEnd ();
	}

	if(Edges)
	{
		glLineWidth(EdgesWidth);
		glColor3ub(EdgeRcolor, EdgeGcolor, EdgeBcolor);

		glBegin (GL_LINE_STRIP);
	
			for(unsigned int i=0; i<=ObjDiv; i++)
				CirclePoints(i, R, R, 0);

		glEnd ();
	}
}

void GL_GEOMETRY_OBJECT::TransformVertex(GLfloat Vx, GLfloat Vy, GLfloat Vz)
{
    v_pos.GetFrom(Vx, Vy, Vz);
    v_pos = v_pos*RotMat;
	v_pos += Base;
            
    glVertex3f (v_pos.x, v_pos.y, v_pos.z);
}

void GL_GEOMETRY_OBJECT::CirclePoints(unsigned int i, GLfloat Rx, GLfloat Ry, GLfloat H)
{
	v_pos.x = Rx*cos(i*ddiv*M_PI/180);
	v_pos.y = Ry*sin(i*ddiv*M_PI/180);
	v_pos.z = H;
	
	v_pos = v_pos*RotMat; 
	v_pos += Base; 

	glVertex3f (v_pos.x, v_pos.y, v_pos.z);            
}
