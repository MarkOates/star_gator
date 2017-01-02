


#include <star_gator/entities/entity_base.h>



Entity3D::Entity3D(ElementID *parent, std::string name, Model3D *model, ALLEGRO_BITMAP *texture)
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



void Entity3D::_draw()
{
   if (renders_self || renders_children) place.start_transform();
   if (renders_children) for (auto &child : get_children<Entity3D>()) child->_draw();
   if (renders_self) draw();
   if (renders_self || renders_children) place.restore_transform();
}



void Entity3D::draw()
{
   if (!model) return;
   model->set_texture(texture);
   model->draw();
}



void Entity3D::inspect()
{
   std::cout << num_children() << std::endl;
   for (auto &e : get_flat_list_of_descendants<Entity3D>())
      std::cout << " - " << e << " " << e->get("name") << " " << e->get_id() << std::endl;
}



