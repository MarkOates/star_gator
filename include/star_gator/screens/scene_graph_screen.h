#pragma once



#include <allegro_flare/screen.h>

#include <star_gator/entities/entity_base.h>



class SceneGraphScreen : public Screen, public EntityBase
{
private:
   void _set_projection(ALLEGRO_BITMAP *bitmap, ALLEGRO_TRANSFORM *t);
   void _update_scene();
   void _draw_scene();

public:
   SceneGraphScreen(Display *display);

   void primary_timer_func() override;
};



