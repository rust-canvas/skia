extern crate euclid;
extern crate gleam;
extern crate skia;
extern crate offscreen_gl_context;

use euclid::{Size2D};
use offscreen_gl_context::{ColorAttachmentType, GLContext, GLContextAttributes, GLVersion, NativeGLContext};

fn main() {
  let gl = match GLContext::<NativeGLContext>::new(
    Size2D::new(1920, 1080),
    GLContextAttributes::default(),
    ColorAttachmentType::Renderbuffer,
    gleam::gl::GlType::Gl,
    GLVersion::Major(4),
    None
  ) {
    Ok(s) => s,
    Err(e) => panic!(e)
  };
  let ctx = unsafe {
    let interface_ref = skia::SkiaGrGLCreateNativeInterface();
    println!("{}", interface_ref.is_null());
    skia::SkiaGrContextCreate(interface_ref)
  };
  println!("{}", ctx.is_null());
}
