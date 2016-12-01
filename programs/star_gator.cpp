


#include <allegro_flare/allegro_flare.h>



class Entity3D : public ElementID
{
public:
   std::string name;
   placement3d place;
   placement3d velocity;
   Model3D *model;
   ALLEGRO_BITMAP *texture;

   bool renders_self, renders_children;

   Entity3D(ElementID *parent, std::string name, Model3D *model=nullptr, ALLEGRO_BITMAP *texture=nullptr)
      : ElementID(parent)
      , name(name)
      , place()
      , velocity()
      , model(model)
      , texture(texture)
      , renders_self(true)
      , renders_children(true)
   {
      Attributes::bind("name", &name);
      velocity.align = vec3d(0, 0, 0);
      velocity.scale = vec3d(0, 0, 0);
   }

   void _draw()
   {
      if (renders_self || renders_children) place.start_transform();
      if (renders_children) for (auto &child : get_children<Entity3D>()) child->_draw();
      if (renders_self) draw();
      if (renders_self || renders_children) place.restore_transform();
   }

   virtual void draw()
   {
      if (!model) return;
      model->set_texture(texture);
      model->draw();
   }
   
   void inspect()
   {
      std::cout << num_children() << std::endl;
      for (auto &e : get_flat_list_of_descendants<Entity3D>())
         std::cout << " - " << e << " " << e->get("name") << " " << e->get_id() << std::endl;
   }
};



class SceneGraphScreen : public Screen, public Entity3D
{
public:
   SceneGraphScreen(Display *display)
      : Screen(display)
      , Entity3D(nullptr, "root")
   {}

   void primary_timer_func() override
   {
      _update_scene();
      _draw_scene();
   }

private:
   void _set_projection(ALLEGRO_BITMAP *bitmap, ALLEGRO_TRANSFORM *t)
   {
      float aspect_ratio = (float)al_get_bitmap_height(bitmap) / al_get_bitmap_width(bitmap);
      al_perspective_transform(t, -1, aspect_ratio, 1, 1, -aspect_ratio, 100);
      al_use_projection_transform(t);
   }

   void _update_scene()
   {
      Screen::primary_timer_func();
      for (auto &e : this->get_flat_list_of_descendants<Entity3D>()) e->place += e->velocity;
   }

   void _draw_scene()
   {
      // setup the render settings
      al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
      al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
      al_clear_depth_buffer(1);

      ALLEGRO_TRANSFORM t;
      Entity3D *camera = static_cast<Entity3D *>(this->find_first("name", "camera"));
      if (camera) camera->place.build_reverse_transform(&t);
      else al_identity_transform(&t);
      _set_projection(backbuffer_sub_bitmap, &t);

      // draw our scene
      this->_draw();
   }

};




class Project : public SceneGraphScreen
{
public:
   Project(Display *display) : SceneGraphScreen(display)
   {
      // create the camera
      Entity3D *camera = new Entity3D(this, "camera");
      camera->place.anchor = vec3d(0, 0, 5);
      camera->velocity.rotation.y = 0.001;
      camera->renders_self = false;
      camera->renders_children = false;

      // create the coin in the middle of the world
      new Entity3D(this, "coin", Framework::model("coin_ring-01.obj"));

      // create the random coins spinning around the room
      for (unsigned i=0; i<10; i++)
      {
         Entity3D *e = new Entity3D(this, "coin", Framework::model("coin_ring-01.obj"));
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
   Display *display = Framework::create_display(800, 600, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   Project *project = new Project(display);
   Framework::run_loop();
   return 0;
}




