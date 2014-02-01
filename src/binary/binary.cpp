#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <algorithm>

#include <nbody-binary/GlutWrapper.h>
#include <nbody-binary/Shaders.h>

namespace nBodyShaders {
  const std::string vertex1(
    "#version 150\n"
    "in vec4 position;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = position;\n"
    "}\n"
  );

  const std::string fragment1(
    "#version 150\n"
    "out vec4 outputColor;\n"
    "void main()\n"
    "{\n"
    "   outputColor = vec4(0.0, 1.0, 0.0, 1.0);"
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
}
int theCount = 0;

void NBodyWindow::display() {
  for( size_t i = 0; i < _bufSize / 4; ++i ) { 
    _buf[4*i] = cosf( 2 * 3.1415f * float( i + theCount / 20000.0f ) / 
      float( _bufSize / 4 ) );
    _buf[4*i+1] = sinf( 2 * 3.1415f * float( i - theCount / 20000.0f ) / 
      float( _bufSize / 4 ) );
    _buf[4*i+2] = 0.0f;
    _buf[4*i+3] = 1.0f;
    theCount++;
  }

  glBindBuffer( GL_ARRAY_BUFFER, _positionBufferObject );
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( float ) * _bufSize, _buf );

  glClearColor( 0.0, 0.0, 0.0, 0.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glUseProgram( _program );
  glDrawArrays( GL_TRIANGLE_STRIP, 0, (GLsizei) _bufSize );
  glUseProgram( 0 );

  glfwSwapBuffers( _window );
  glfwPollEvents();
}

static void error_callback( int error, const char *description ) {
  std::cerr << "Error number: " << error << std::endl;
  throw std::runtime_error( description );
}

int main( int argc, char ** argv ) {
  try {
		size_t N = 12;
		size_t bufSize = 4 * N;
		float *buf = new float[bufSize];

		for( size_t i = 0; i < N; ++i ) {
			buf[4*i] = cosf( 2 * 3.1415f * float( i ) / float( N ) );
			buf[4*i+1] = sinf( 2 * 3.1415f * float( i ) / float( N ) );
			buf[4*i+2] = 0.0f;
			buf[4*i+3] = 1.0f;
			std::cout << buf[4*i] << " " << buf[4*i+1];
      std::cout << " " << buf[4*i+2] << " " << buf[4*i+3] << "\n";
    }

    glfwSetErrorCallback( error_callback );

		Shaders shaders;
		shaders.addToVertexList( nBodyShaders::vertex1 );
		shaders.addToFragmentList( nBodyShaders::fragment1 );
    NBodyWindow window{ "N-Body Simulation", GlutWrapper::NDEBUG };
		window.init( argc, argv, 500, 500, &shaders, bufSize, buf );
		window.run();

		delete [] buf;
    return 0;
  } catch( const std::exception &e ) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
