#pragma once



#include <allegro_flare/screen.h>

#include <star_gator/entity3d.h>



class SceneGraphScreen : public Screen, public Entity3D
{
private:
   void _set_projection(ALLEGRO_BITMAP *bitmap, ALLEGRO_TRANSFORM *t);
   void _update_scene();
   void _draw_scene();

public:
   SceneGraphScreen(Display *display);

   void primary_timer_func() override;
};



