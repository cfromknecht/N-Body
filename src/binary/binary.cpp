#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <algorithm>

#include <nbody/Integrator.h>
#include <nbody/CelestialSystem.h>
#include <nbody-demo/GlutWrapper.h>
#include <nbody-demo/Shaders.h>
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace nBodyShaders {
  const std::string vertex1(
    "#version 150\n"
    "in vec4 position;\n"
    "uniform float scale;\n"
    "uniform mat4 projectionMatrix;\n"
    "uniform mat4 modelViewMatrix;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projectionMatrix*modelViewMatrix*position;\n"
    "   gl_PointSize = 20.0f;\n"
    "}\n"
  );
    /*"uniform float xAngle;\n"
    "uniform float yAngle;\n"
    "uniform float zAngle;\n"
    "mat4 xMat = mat4(\n"
    "   (1-cos(xAngle)) + cos(xAngle), 0, 0, 0,\n"
    "   0, cos(xAngle), -sin(xAngle), 0,\n"
    "   0, sin(xAngle), cos(xAngle), 0,\n"
    "   0, 0, 0, 1);\n"
    "mat4 yMat = mat4(\n"
    "   cos(yAngle), 0, sin(yAngle), 0,\n"
    "   0, (1-cos(yAngle)) + cos(yAngle), 0, 0,\n"
    "   -sin(yAngle), 0, cos(yAngle), 0,\n"
    "   0, 0, 0, 1);\n"
    "mat4 zMat = mat4(\n"
    "   0, -sin(zAngle), 0, 0,\n"
    "   sin(zAngle), cos(zAngle), 0, 0,\n"
    "   0, 0, (1 - cos(zAngle)) + cos(zAngle), 0,\n"
    "   0, 0, 0, 1);\n"*/

  const std::string fragment1(
    "#version 150\n"
    "out vec4 outputColor;\n"
    "uniform float xAngle;\n"
    "uniform float yAngle;\n"
    "uniform float zAngle;\n"
    "mat4 xMat = mat4(\n"
    "   (1-cos(xAngle)) + cos(xAngle), 0, 0, 0,\n"
    "   0, cos(xAngle), -sin(xAngle), 0,\n"
    "   0, sin(xAngle), cos(xAngle), 0,\n"
    "   0, 0, 0, 1);\n"
    "mat4 yMat = mat4(\n"
    "   cos(yAngle), 0, sin(yAngle), 0,\n"
    "   0, (1-cos(yAngle)) + cos(yAngle), 0, 0,\n"
    "   -sin(yAngle), 0, cos(yAngle), 0,\n"
    "   0, 0, 0, 1);\n"
    "mat4 zMat = mat4(\n"
    "   0, -sin(zAngle), 0, 0,\n"
    "   sin(zAngle), cos(zAngle), 0, 0,\n"
    "   0, 0, (1 - cos(zAngle)) + cos(zAngle), 0,\n"
    "   0, 0, 0, 1);\n"
    "void main()\n"
    "{\n"
    "   vec3 N;"
    "   N.xy = gl_PointCoord*2.0 - vec2(1.0);\n"
    "   float mag = dot(N.xy, N.xy);\n"
    "   if (mag > 1.0) discard;\n"
    "   N.z = sqrt(1.0 - mag);\n"
    "   float diffuse = max(0.0, dot(vec3(1.0,1.0,1.0), N));\n"
    "   outputColor = vec4(1.0, 0.0, 0.0, 1.0)*diffuse;\n"
    "}\n"
  );
} // namespace shaders

class NBodyWindow : public GlutWrapper {
  
public:
	NBodyWindow( const std::string &title, 
               Mode debugMode = Mode::NDEBUG );
  ~NBodyWindow();

  void display();
  void reshape( int theWidth, int theHeight );
  void keyboard( unsigned char key, int x, int y );
  int orientation;
};

NBodyWindow::NBodyWindow( const std::string &title, Mode debugMode ) : 
  GlutWrapper{ title, debugMode } {
	_instance = this; 
}

NBodyWindow::~NBodyWindow() {}

void NBodyWindow::reshape( int theWidth, int theHeight ) {
	glViewport( 0, 0, (GLsizei) theWidth, (GLsizei) theHeight );
}

void NBodyWindow::keyboard( unsigned char key, int /*x*/, int /*y*/ ) {
	const char ESCAPE_KEY = 27;
  if( key == ESCAPE_KEY ) {
    exit(0);
  }
  //if (glfwGetKey( GLFW_KEY_UP) == GLFW_PRESS) {
      
}
int theCount = 0;
int zoom = 1;
int speed = 10;
float xAngle = 0.0f;
float yAngle = 0.0f;
float zAngle = 0.0f;
bool pause = false;
std::fstream sysFile{ "resources/nbody/binary-system-simple.txt" }; 
auto es = RK4<CelestialSystem> (sysFile);
ParticleSystem *sys = es.getSystem();

void NBodyWindow::display() {

  if (theCount%speed == 0 && !pause) {
    es.step(0.001f);
  }
  for( size_t j = 0; j < _bufSize / 4; ++j ) { 
    _buf[4*j] = sys->getPosition(j).x();
    _buf[4*j + 1] = sys->getPosition(j).y();
    _buf[4*j + 2] = sys->getPosition(j).z();
    _buf[4*j + 3] = 1.0f;
  }

  glm::mat4 projectionMatrix = glm::perspective(0.75f, 1.0f, 0.01f, 5.0f);
  glm::mat4 modelViewMatrix = glm::lookAt(glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
  modelViewMatrix = glm::rotate(modelViewMatrix, xAngle, glm::vec3(1,0,0));
  modelViewMatrix = glm::rotate(modelViewMatrix, yAngle, glm::vec3(0,1,0));
  modelViewMatrix = glm::rotate(modelViewMatrix, zAngle, glm::vec3(0,0,1));
  glBindBuffer( GL_ARRAY_BUFFER, _positionBufferObject );
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( float ) * _bufSize, _buf );

  glClearColor( 0.0, 0.0, 0.0, 0.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glUseProgram( _program );
  GLint scaleLoc = glGetUniformLocation( _program, "scale");
  if (scaleLoc != -1) {
     glUniform1f(scaleLoc, (float) zoom) ;
  }
  GLint projectionLoc = glGetUniformLocation( _program, "projectionMatrix" );
  if (projectionLoc != -1) {
     glUniformMatrix4fv(projectionLoc,1.0,0, &projectionMatrix[0][0]) ;
  }
  GLint modelLoc = glGetUniformLocation( _program, "modelViewMatrix" );
  if (modelLoc != -1) {
     glUniformMatrix4fv(modelLoc, 1.0,0,&modelViewMatrix[0][0]) ;
  }

  glDrawArrays( GL_POINTS, 0, (GLsizei) _bufSize/sys->getN());
  glUseProgram( 0 );

  glfwSwapBuffers( _window );
  // wtf does this do and why is it here????
  glfwPollEvents();
  theCount++;
}

static void error_callback( int error, const char *description ) {
  std::cerr << "Error number: " << error << std::endl;
  throw std::runtime_error( description );
}

static void key_callback(GLFWwindow *window, int key, int /*scancode*/, int action, int /*mods*/) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose( window, GL_TRUE );
    } else if (key == GLFW_KEY_J && action == GLFW_PRESS) {
        if (speed < 20) {
            speed++;
        }
    } else if (key == GLFW_KEY_K && action == GLFW_PRESS) {
        if (speed > 1) {
            speed--;
        }
    } else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        pause = !pause;
    } else if (key == GLFW_KEY_I && action == GLFW_PRESS) {
        if (zoom < 40) {
            zoom++;
        }
    } else if (key == GLFW_KEY_O && action == GLFW_PRESS) {
        if (zoom > 1) {
            zoom--;
        }
    } else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        xAngle += 0.01f;
    } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        xAngle -= 0.01f;
    } else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        zAngle += 0.01f;
    } else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        zAngle -= 0.01f;
    }
}

int main( int argc, char ** argv ) {
  try {
		size_t N = sys->getN();
		size_t bufSize = 4 * N;
		float *buf = new float[bufSize];


    for (size_t j = 0; j < N; ++j) {
        buf[4*j] = sys->getPosition(j).x();
        buf[4*j + 1] = sys->getPosition(j).y();
        buf[4*j + 2] = sys->getPosition(j).z();
        buf[4*j + 3] = 1.0f;
    }
        


        glfwSetErrorCallback( error_callback );
		Shaders shaders;
		shaders.addToVertexList( nBodyShaders::vertex1 );
		shaders.addToFragmentList( nBodyShaders::fragment1 );
        NBodyWindow window{ "N-Body Simulation", GlutWrapper::NDEBUG };
		window.init( argc, argv, 500, 500, &shaders, bufSize, buf );
        glfwMakeContextCurrent( window.getWindow() );
        glfwSetKeyCallback( window.getWindow(), key_callback);
		window.run();

		delete [] buf;
    return 0;
  } catch( const std::exception &e ) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
