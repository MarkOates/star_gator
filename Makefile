


# here are the directories of the projects
# LIBS_ROOT=E:
LIBS_ROOT=/Users/markoates/Repos
ALLEGRO_DIR=$(LIBS_ROOT)/allegro5/build
ALLEGRO_FLARE_DIR=$(LIBS_ROOT)/allegro_flare
STAR_GATOR_DIR=$(LIBS_ROOT)/star_gator



# these are the names of the libs you are linking
ALLEGRO_FLARE_LIB=allegro_flare-0.8.8wip
ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro_main -lallegro
OPENGL_LIB=-framework OpenGL
# OPENGL_LIB=-lopengl32



.PHONY: all clean main



SOURCES := $(shell find src -name '*.cpp')
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)



bin/star_gator: programs/star_gator.cpp $(OBJECTS)
	g++ -std=gnu++11 $(OBJECTS) $< -o $@ -l$(ALLEGRO_FLARE_LIB) $(ALLEGRO_LIBS) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib $(OPENGL_LIB) -I$(ALLEGRO_FLARE_DIR)/include -I$(ALLEGRO_DIR)/include -I./include



obj/%.o: src/%.cpp
	g++ -c -std=gnu++11 $< -o $@ -I$(ALLEGRO_FLARE_DIR)/include -I$(ALLEGRO_DIR)/include -I./include



clean:
	-rm $(OBJECTS)
	-rm bin/star_gator



