#pragma once



#include <allegro_flare/element_id.h>
#include <allegro_flare/model3d.h>
#include <allegro_flare/placement3d.h>
#include <allegro5/allegro_image.h>



class EntityBase : public ElementID
{
public:
   placement3d place;
   placement3d velocity;
   Model3D *model;
   ALLEGRO_BITMAP *texture;

   bool renders_self, renders_children;

   EntityBase(ElementID *parent, std::string type, Model3D *model=nullptr, ALLEGRO_BITMAP *texture=nullptr);

   void _draw();

   virtual void draw();

   void inspect();
};



