#include <Render/Camera.h>
#include <Render/NodeVisitor.h>
#include <Core/WindowEvent.h>
#include <iostream>
#include <Core/Utility.h>
#include <Render/Scene.h>
#include <Render/Node.h>

namespace vrv
{
  Camera::Camera()
    : myYaw(-90)
    , myPitch(0)
    , myRoll(0)
    , myUp(0, 1, 0)
    , myFront(0, 0, -1)
    , myRight(1, 0, 0)
    , myPosition(0, 0, 3)
    , myMoveSpeed(10.0f)
    , myRotateSpeed(0.02f)
    , myZoomSpeed(0.02f)
    , myFirstMouse(true)
    , myLastMouseX(0)
    , myLastMouseY(0)
    , myFOV(45)
    , myNearPlane(0.1f)
    , myFarPlane(100.0f)
    , myInitialPosition(Vector3f(0, 0, 10))
    , myWDivideH(4.0f / 3.0f)
    , myCameraMode(FreeMove)
    , myLastFrame(0)
  {
   

    intrinsic_ = Matrix3f(868.6247f, 0, 512 , 0 , 868.6247f, 288, 0 , 0 , 1);


    float fx = intrinsic_[0][0];
    float fy = intrinsic_[1][1];
    float fov = Utility::RadianToDegree(2 * Utility::atan2(576, 2 * fy));


    myProjectionMatrix = Matrix4f::makeProjection(fov, 1024.0/576.0, myNearPlane, myFarPlane);
  }

  Camera::Camera(Matrix4f& extrinsic, Matrix3f& intrinsic, Vector4f& distortion) {
    extrinsic_ = extrinsic;
    intrinsic_ = intrinsic;
    distortion_ = distortion;

    

  }

  void Camera::setProjectionMatrixAsPerspective(float verticalFieldOfView, float ratioWDivedeH, float n, float f)
  {
    myFOV = verticalFieldOfView;
    myWDivideH = ratioWDivedeH;
    myNearPlane = n;
    myFarPlane = f;
    myProjectionMatrix = Matrix4f::makeProjection(verticalFieldOfView, ratioWDivedeH, n, f);
  }

  void Camera::setProjectionMatrixAsPerspective(float l, float r, float b, float t, float n, float f)
  {
    myProjectionMatrix = Matrix4f::makeProjection(l, r, b, t, n, f);
  }

  void Camera::setProjectionMatrixAsOrtho(float l, float r, float b, float t, float n, float f)
  {
    myProjectionMatrix = Matrix4f::makeWindowingTransformation(l, b, n, r, t, f, -1, -1, -1, 1, 1, 1);
  }

  void Camera::setProjectionMatroxAsOrtho2D(float l, float r, float b, float t)
  {
    setProjectionMatrixAsOrtho(l, r, b, t, 0, 1);
  }

  void Camera::reset()
  {
    myYaw = -90;
    myPitch = 0;
    myRoll = 0;
    myFront = Vector3f(0, 0, -1);
    myRight = Vector3f(1, 0, 0);
    myUp = Vector3f(0, 1, 0);
    myPosition = myInitialPosition;
    myFOV = 45;
    myFirstMouse = true;
    myLastMouseX = 0;
    myLastMouseY = 0;
  }

  void Camera::updateVectors()
  {
    myFront.normalize();
    Vector3f w = -myFront;
    myRight = myUp.crossProduct(w);
    myUp = w.crossProduct(myRight);
  }

  Matrix4f Camera::getViewMatrix()
  {
    Vector3f w = -myFront.normalizedVector();
    return Matrix4f::makeCanonicalToFrame(myPosition, myRight, myUp, w);
  }

  Matrix4f Camera::projectionMatrix()
  {
    float k1 = -46.19076504532866;
    float k2 = 25.455138686362;


    Matrix4f view = getViewMatrix();
    Matrix4f intri(intrinsic_);

    std::vector<Vector4f> vecs = {Vector4f(-0.5f, 0.5f, 0.0f, 1.0f), Vector4f(-0.5f, -0.5f, 0.0f, 1.0f) ,
    Vector4f(0.5f, -0.5f, 0.0f, 1.0f) ,Vector4f(0.5f, 0.5f, 0.0f, 1.0f) };

    std::vector<Vector3f> no_distortion;
    std::vector<Vector3f> distortion;
    std::vector<Vector3f> no_distortion_ndc;
    std::vector<Vector3f> distortion_ndc;
    std::vector<Vector4f> projection;
    std::vector<Vector4f> projection_ndc;

    Matrix3f scale_ndc = Matrix3f::makeScale(1.0f / 1024.0f, 1.0f / 576.0f);




    for (Vector4f vec : vecs) {

      Vector4f view_coor = view  * vec;
      Vector3f projected_view = Vector3f(view_coor.x() / abs(view_coor.z()),
        view_coor.y() / abs(view_coor.z()), 1.0);

      float xc = projected_view.x();
      float yc = projected_view.y();
      float rc2 = xc * xc + yc * yc;

      float k1 = -0.4619076504532866;
      float k2 = 0.25455138686362;

      float xc_distortion = xc * (1 + k1 * rc2 + k2 * rc2*rc2);
      float yc_distortion = yc * (1 + k1 * rc2 + k2 * rc2*rc2);

      projected_view.x() = xc_distortion;
      projected_view.y() = yc_distortion;
      Vector3f distortion_vec = intrinsic_ * projected_view;
      float distortion_ndc_x = 2.0f * distortion_vec.x() / 1024.0f - 1.0f;;
      float distortion_ndc_y = 2.0f * distortion_vec.y() / 576.0f - 1.0f;

      Vector4f gl_Position = myProjectionMatrix * view *vec;

      gl_Position.x() = distortion_ndc_x * gl_Position.w();
      gl_Position.y() = distortion_ndc_y * gl_Position.w();


      

      //Vector4f proj_vec = myProjectionMatrix * view * vec;
      //projection.push_back(proj_vec);

      //projection_ndc.emplace_back(proj_vec.x() / proj_vec.w(), proj_vec.y() / proj_vec.w(),
      //  proj_vec.z() / proj_vec.w(), proj_vec.w() / proj_vec.w());

      //Vector4f view_coor = view * vec;
      //Vector3f projected_view = Vector3f(view_coor.x() / -view_coor.z(), view_coor.y() / -view_coor.z(), 1.0);

      //float xc = projected_view.x();
      //float yc = projected_view.y();
      //float rc2 = xc * xc + yc * yc;

      //float xc_distortion = xc * (1 + k1 * rc2 + k2 * rc2*rc2);
      //float yc_distortion = yc * (1 + k1 * rc2 + k2 * rc2*rc2);

      //Vector3f no_distortion_vec = intrinsic_ * projected_view;
      //no_distortion.push_back(no_distortion_vec);
      //no_distortion_vec.x() = 2.0f * no_distortion_vec.x() / 1024.0f - 1.0f;;
      //no_distortion_vec.y() = 2.0f * no_distortion_vec.y() / 576.0f - 1.0f;
      //no_distortion_ndc.push_back(no_distortion_vec);

      //projected_view.x() = xc_distortion;
      //projected_view.y() = yc_distortion;

      //Vector3f distortion_vec = intrinsic_ * projected_view;
      //distortion.push_back(distortion_vec);
      //distortion_vec.x() = 2.0f * distortion_vec.x() / 1024.0f - 1.0f;;
      //distortion_vec.y() = 2.0f * distortion_vec.y() / 576.0f - 1.0f;
      //distortion_ndc.push_back(distortion_vec);

      //proj_vec.x() = distortion_vec.x() * proj_vec.w();
      //proj_vec.y() = distortion_vec.y() * proj_vec.w();

      std::cout << "";
    }


    return myProjectionMatrix;
  }



  void Camera::handleWheelEvent(const WindowEvent& e)
  {
    if (myFOV >= 1.0f && myFOV <= 45.0f)
    {
      myFOV -= e.wheelDelta()*myZoomSpeed;
    }
    if (myFOV <= 1.0f)
      myFOV = 1.0f;
    if (myFOV >= 45.0f)
      myFOV = 45.0f;
    myProjectionMatrix = Matrix4f::makeProjection(myFOV, myWDivideH, myNearPlane, myFarPlane);
  }

  Vector3f Camera::position()
  {
    return myPosition;
  }

  void Camera::setInitialPosition(Vector3f position)
  {
    myInitialPosition = position;
    reset();
  }

  void Camera::focousOnTarget(Vector3f position, float radius)
  {
    myNearPlane = 0.01f * radius;
    myFarPlane = 10 * radius;

    float distance = radius / Utility::sin(myFOV / 2.0f);

    myPosition = Vector3f(0, 0, 1) * distance + position;
    setInitialPosition(myPosition);
    myProjectionMatrix = Matrix4f::makeProjection(myFOV, myWDivideH, myNearPlane, myFarPlane);
  }

  void Camera::focousOnTarget(Node* node)
  {
    if (node)
    {
      Vector3f position = node->position();
      Bound bound = node->bound();
      focousOnTarget(bound.center(), bound.radius());
    }
  }

  void Camera::orbitMode(const WindowEvent& e)
  {
    static float startX = 0;
    static float startY = 0;
    static ApplyRotationNodeVisitor v;
    switch (e.eventType())
    {
    case WindowEvent::MouseDown:
    {
      startX = e.mousePositionX();
      startY = e.mousePositionY();

    };
    break;
    case WindowEvent::MouseUp:
    {
    };
    break;
    case WindowEvent::MouseMove:
    {
      if (e.mouseButton() == WindowEvent::LeftMouseButton)
      {
        float deltaX = e.mousePositionX() - startX;
        float deltaY = e.mousePositionY() - startY;
        float speed = 0.01f;
        v.setXRotation(deltaY*speed);
        v.setYRotation(deltaX*speed);
        Scene::instance().acceptNodeVisitor(&v);
      }
    };
    break;
    };
  }

  void Camera::setLastFrame(double t)
  {
    myLastFrame = t;
  }

  void Camera::freeMode(const WindowEvent& e)
  {
    switch (e.eventType())
    {
    case WindowEvent::KeyBoardDown:
    {
      switch (e.keyButton())
      {
      case WindowEvent::W:
      {
        myPosition += myFront * myMoveSpeed * myLastFrame;
      }
      break;
      case WindowEvent::S:
      {
        myPosition -= myFront * myMoveSpeed * myLastFrame;
      }
      break;
      case WindowEvent::A:
      {
        myPosition -= myRight * myMoveSpeed * myLastFrame;
      }
      break;
      case WindowEvent::D:
      {
        myPosition += myRight * myMoveSpeed * myLastFrame;
      }
      break;
      case WindowEvent::Z:
      {
        reset();
      }
      break;
      default:
        break;
      }
    }
    break;
    case WindowEvent::MouseMove:
    {
      if (myFirstMouse)
      {
        myLastMouseX = e.mousePositionX();
        myLastMouseY = e.mousePositionY();
        myFirstMouse = false;
      }
      if (e.mouseButton() == WindowEvent::RightMouseButton)
      {
        float deltaX = e.mousePositionX() - myLastMouseX;
        float deltaY = e.mousePositionY() - myLastMouseY;


        myLastMouseX = e.mousePositionX();
        myLastMouseY = e.mousePositionY();

        myYaw += deltaX * myRotateSpeed;
        myPitch -= deltaY * myRotateSpeed;

        if (myPitch > 89.0f)
          myPitch = 89.0f;
        if (myPitch < -89.0f)
          myPitch = -89.0f;

        myFront.x() = Utility::cos(myPitch)*Utility::cos(myYaw);
        myFront.y() = Utility::sin(myPitch);
        myFront.z() = Utility::cos(myPitch) * Utility::sin(myYaw);
        updateVectors();
      }
      else
      {
        myLastMouseX = e.mousePositionX();
        myLastMouseY = e.mousePositionY();
      }
    }
    break;
    default:
      break;
    }
  }

  void Camera::handleWindowEvent(const WindowEvent& e)
  {
    switch (e.eventType())
    {
    case WindowEvent::KeyBoardDown:
    {
      switch (e.keyButton())
      {
      case WindowEvent::X:
      {
        myCameraMode = (CameraMode)((myCameraMode + 1) % 2);
      }
      }
    }
    break;
    case WindowEvent::Wheel:
    {
      handleWheelEvent(e);
    }
    break;
    }


    switch (myCameraMode)
    {
    case vrv::Camera::OrbitMode:
      orbitMode(e);
      break;
    case vrv::Camera::FreeMove:
      freeMode(e);
      break;
    default:
      break;
    }
  }
}