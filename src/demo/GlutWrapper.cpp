#include "GlutWrapper.h"
#include "Shaders.h"

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
/*
  glutInit( &argc, argv );
  uint32_t displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL;

  glutInitDisplayMode( displayMode );
  glutInitContextVersion( 3, 2 );
  glutInitContextFlags( GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG );
  glutInitContextProfile( GLUT_CORE_PROFILE );

  if ( _debugMode == Mode::DEBUG )
    glutInitContextFlags( GLUT_DEBUG );
*/
	if( shaders == nullptr ) {
		throw std::runtime_error( "GlutWrapper::init was provided null Shaders pointer" );
  }

	createWindow();
	_program = shaders->build();
	initVertexBuffers( bufSize, buf );
  glGenVertexArrays( 1, &_vao );
  glBindVertexArray( _vao );
  glEnableVertexAttribArray( 0 );
  glBindBuffer( GL_ARRAY_BUFFER, _positionBufferObject );
  glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );
}

void GlutWrapper::createWindow() {
  if ( !glfwInit() )
    exit( EXIT_FAILURE );
/*
  glutInitWindowSize( _width, _height );
  _windowId = glutCreateWindow( _windowTitle.c_str() );
*/
  glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
  glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

  _window = glfwCreateWindow( _width, _height, _windowTitle.c_str(), nullptr, nullptr );
  glfwMakeContextCurrent( _window );

  std::cout << "Using OpenGL Version " << glfwGetWindowAttrib( _window, GLFW_CONTEXT_VERSION_MAJOR );
  std::cout << "." << glfwGetWindowAttrib( _window, GLFW_CONTEXT_VERSION_MINOR ) << std::endl;

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if ( GLEW_OK != err )
    throw std::runtime_error( "GLEW failed to initialize" );
/*
  if ( _debugMode == Mode::DEBUG ) {
    if ( __GLEW_ARB_debug_output ) {
      glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB );
      glDebugMessageCallbackARB( (GLDEBUGPROCARB) openglDebug, (void*) 15 );
    }
  }
*/
}

void GlutWrapper::initVertexBuffers( size_t bufSize, float *buf ) {
  glGenBuffers( 1, &_positionBufferObject );

  glBindBuffer( GL_ARRAY_BUFFER, _positionBufferObject );
	if( buf == nullptr ) {
		throw std::runtime_error( "Provided a null buffer to initVertexBuffers." );
  } else {
		_bufSize = bufSize;
		_buf = buf;
		glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * bufSize, _buf, GL_STATIC_DRAW );
  }
}

void GlutWrapper::run() {
/*
  glBindVertexArrayAPPLE( _vao );
  glutDisplayFunc( displayCallback );
  glutReshapeFunc( reshapeCallback );
  glutKeyboardFunc( keyboardCallback );
  glutMainLoop();
*/
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

