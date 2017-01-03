


#include <allegro_flare/allegro_flare.h>

#include <star_gator/screens/scene_graph_screen.h>



class Project : public SceneGraphScreen
{
public:
   Project(Display *display) : SceneGraphScreen(display)
   {
      // create the camera
      EntityBase *camera = new EntityBase(this, "camera");
      camera->place.anchor = vec3d(0, 0, 5);
      camera->velocity.rotation.y = 0.001;
      camera->renders_self = false;
      camera->renders_children = false;

      // create the coin in the middle of the world
      new EntityBase(this, "coin", Framework::model("coin_ring-01.obj"));

      // create the random coins spinning around the room
      for (unsigned i=0; i<10; i++)
      {
         EntityBase *e = new EntityBase(this, "coin", Framework::model("coin_ring-01.obj"));
         e->texture = Framework::bitmap("uv.png");
         e->place.position.x = random_float(-2, 2);
         e->place.position.y = random_float(-2, 2);
         e->place.position.z = random_float(-2, 2);
         e->place.rotation.y = random_float(0, 1.0);
         e->velocity.rotation.y = 0.005;
      }
   }
};



int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display(1280, 720, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   Project *project = new Project(display);
   Framework::run_loop();
   return 0;
}



