


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


# this is the EXE extension that is used (if any)
EXE_EXTENSION=
# EXE_EXTENSION=.exe




.PHONY: all clean



ALL_OBJ_BASENAMES=$(basename $(notdir $(wildcard src/*.cpp)))
ALL_PROGRAM_BASENAMES=$(basename $(notdir $(wildcard programs/*.cpp)))
ALL_PROGRAM_EXES=$(addprefix bin/, $(addsuffix $(EXE_EXTENSION), $(ALL_PROGRAM_BASENAMES)))
ALL_OBJ_OBJS=$(addprefix obj/, $(addsuffix .o, $(ALL_OBJ_BASENAMES)))


all: $(ALL_PROGRAM_EXES)



bin/%$(EXE_EXTENSION): programs/%.cpp $(ALL_OBJ_OBJS)
	g++ -std=gnu++11 $(ALL_OBJ_OBJS) $< -o $@ -l$(ALLEGRO_FLARE_LIB) $(ALLEGRO_LIBS) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib $(OPENGL_LIB) -I$(ALLEGRO_FLARE_DIR)/include -I$(ALLEGRO_DIR)/include -I./include



$(ALL_OBJ_OBJS): obj/%.o : src/%.cpp
	g++ -c -std=gnu++11 $< -o $@ -I$(ALLEGRO_FLARE_DIR)/include -I$(ALLEGRO_DIR)/include -I$(STAR_GATOR_DIR)/include
	#g++ -c -Wall -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

obj/%.o: src/$(notdir $(basename $%)).cpp 



clean:
	-rm $(ALL_OBJ_OBJS)
	-rm $(ALL_PROGRAM_EXES)



