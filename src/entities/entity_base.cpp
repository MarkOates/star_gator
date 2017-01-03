


#include <star_gator/entities/entity_base.h>



EntityBase::EntityBase(ElementID *parent, std::string name, Model3D *model, ALLEGRO_BITMAP *texture)
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



void EntityBase::_draw()
{
   if (renders_self || renders_children) place.start_transform();
   if (renders_children) for (auto &child : get_children<EntityBase>()) child->_draw();
   if (renders_self) draw();
   if (renders_self || renders_children) place.restore_transform();
}



void EntityBase::draw()
{
   if (!model) return;
   model->set_texture(texture);
   model->draw();
}



void EntityBase::inspect()
{
   std::cout << num_children() << std::endl;
   for (auto &e : get_flat_list_of_descendants<EntityBase>())
      std::cout << " - " << e << " " << e->get("name") << " " << e->get_id() << std::endl;
}



