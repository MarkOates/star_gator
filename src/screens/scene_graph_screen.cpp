


#include <star_gator/screens/scene_graph_screen.h>



SceneGraphScreen::SceneGraphScreen(Display *display)
   : Screen(display)
   , EntityBase(nullptr, "root")
{}



void SceneGraphScreen::primary_timer_func()
{
   _update_scene();
   _draw_scene();
}



void SceneGraphScreen::_set_projection(ALLEGRO_BITMAP *bitmap, ALLEGRO_TRANSFORM *t)
{
   float aspect_ratio = (float)al_get_bitmap_height(bitmap) / al_get_bitmap_width(bitmap);
   al_perspective_transform(t, -1, aspect_ratio, 1, 1, -aspect_ratio, 100);
   al_use_projection_transform(t);
}



void SceneGraphScreen::_update_scene()
{
   Screen::primary_timer_func();
   for (auto &e : this->get_flat_list_of_descendants<EntityBase>()) e->place += e->velocity;
}



void SceneGraphScreen::_draw_scene()
{
   // setup the render settings
   al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
   al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
   al_clear_depth_buffer(1);

   ALLEGRO_TRANSFORM t;
   EntityBase *camera = static_cast<EntityBase *>(this->find_first("name", "camera"));
   if (camera) camera->place.build_reverse_transform(&t);
   else al_identity_transform(&t);
   _set_projection(backbuffer_sub_bitmap, &t);

   // draw our scene
   this->_draw();
}



