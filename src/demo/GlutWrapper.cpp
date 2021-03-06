#include <nbody-demo/GlutWrapper.h>
#include <nbody-demo/Shaders.h>


GlutWrapper *GlutWrapper::_instance = nullptr;

GlutWrapper::GlutWrapper() : 
  _shaders{nullptr}, _width{}, _height{}, 
  _window{}, _windowTitle{},
  _bufSize{}, _buf{nullptr}, _positionBufferObject{},
  _vao{}, _program{}, _debugMode{Mode::NDEBUG} {}

GlutWrapper::GlutWrapper( Mode debugMode ) : 
  _shaders{nullptr}, _width{}, _height{}, 
  _window{}, _windowTitle{},
  _bufSize{}, _buf{nullptr}, _positionBufferObject{},
  _vao{}, _program{}, _debugMode{debugMode} {}

GlutWrapper::GlutWrapper( const std::string &title, Mode debugMode ) : 
  _shaders{nullptr}, _width{}, _height{}, 
  _window{}, _windowTitle{title},
  _bufSize{}, _buf{nullptr}, _positionBufferObject{},
  _vao{}, _program{}, _debugMode{debugMode} {}

GlutWrapper::~GlutWrapper() { 
  // shaders should be managed outside the program
}

void GlutWrapper::init( int /* argc */, char **argv, 
                        int theWidth, int theHeight, 
                        Shaders *shaders, 
                        size_t bufSize, float *buf ) {
	_width = theWidth;
	_height = theHeight;
	if( _windowTitle == "" ) {
		_windowTitle = std::string( argv[0] );
  }
	if( shaders == nullptr ) {
		throw std::runtime_error( "GlutWrapper::init was provided null Shaders "
      "pointer" );
  }

	createWindow();
	_program = shaders->build();
	initVertexBuffers( bufSize, buf );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glEnable( GL_POINT_SPRITE );
  glEnable( GL_VERTEX_PROGRAM_POINT_SIZE );
  glGenVertexArrays( 1, &_vao );
  glBindVertexArray( _vao );
  glEnableVertexAttribArray( 0 );
  glBindBuffer( GL_ARRAY_BUFFER, _positionBufferObject );
  glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );
}

void GlutWrapper::createWindow() {
  if ( !glfwInit() )
    exit( EXIT_FAILURE );

  glfwWindowHint( GLFW_RESIZABLE, GL_TRUE );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
  glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

  _window = glfwCreateWindow( _width, _height, _windowTitle.c_str(), nullptr, 
    nullptr );
  glfwMakeContextCurrent( _window );

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if ( GLEW_OK != err )
    throw std::runtime_error( "GLEW failed to initialize" );
}

GLFWwindow* GlutWrapper::getWindow() {
    return _window;
}

void GlutWrapper::initVertexBuffers( size_t bufSize, float *buf ) {
  glGenBuffers( 1, &_positionBufferObject );

  glBindBuffer( GL_ARRAY_BUFFER, _positionBufferObject );
	if( buf == nullptr ) {
		throw std::runtime_error( "Provided a null buffer to initVertexBuffers." );
  } else {
		_bufSize = bufSize;
		_buf = buf;
		glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * bufSize, _buf, 
      GL_STATIC_DRAW );
  }
}

void GlutWrapper::run() {
  while ( !glfwWindowShouldClose( _window ) )
    display();
  
  glfwDestroyWindow( _window );
}



// Jason L. McKesson's helpful debugging function
// See http://www.arcsynthesis.org/gltut/
void GlutWrapper::displayCallback() {
	_instance->display();
}

void GlutWrapper::reshapeCallback( int theWidth, int theHeight ) {
	_instance->reshape( theWidth, theHeight );
}

void GlutWrapper::mouseCallback( int button, int state, int x, int y ) {
	_instance->mouse( button, state, x, y );
}

void GlutWrapper::keyboardCallback( unsigned char key, int x, int y ) {
	_instance->keyboard( key, x, y );
}

// By default, don't do anything on a mouse click
void GlutWrapper::mouse( int /*button*/, int /*state*/, int /*x*/, int /*y*/ ) {}

// By default, don't do anything on a key press
void GlutWrapper::keyboard( unsigned char /*key*/, int /*x*/, int /*y*/ ) {}

