#### Common settings 

PROJECT		:= case_study_yandex
TMPDIR          := $$HOME/tmp/$(PROJECT)
TMPDIR2SVN      := $$HOME/tmp/$(PROJECT)/SVN
CURDIR          :=${shell pwd }
Dirs		:= ${shell find . -type d | grep -v ".svn" | grep  "./"}

### SVN repo settings
SVNREPO 	:= https://my-code-iggy-floyd-de.googlecode.com/svn/branches
SVNUSER	       	:= iggy.floyd.de@gmail.com

### GIT repo settings
GITREPOPATH     := https://api.github.com/user/repos
GITREPO         := $(PROJECT)
TMPDIR2GIT      := $$HOME/tmp/$(PROJECT)/GIT
GITUSER         :=   igormarfin


### Compilers settings for C/C++/JAVA 
CXX				:= g++ 
CPPFLAGS		:=-g 
JAVA            := javac
JAVA_EXE        := java
JAR				:= jar

### settings for bin/src/includes   of C/C++ projects


SRC_DIR 		:= src
BIN_DIR			:= bin
INC_DIR			:= include


INCLUDES		:= $(addprefix -I, $(INC_DIR))
SRC				:= $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cc))
PROGS			:= $(patsubst $(SRC_DIR)/%.cc,%,$(SRC))
HEADERS			:= $(patsubst $(SRC_DIR)/%.cc,$(INC_DIR)/%.h,$(SRC))
PROGS_IN_BIN	:= $(patsubst src/%.cc,$(BIN_DIR)/%,$(SRC))



#### python programs settings



PYTHON_DIR      := scripts
PYTHON_INSTALL  := $(shell echo `pwd`/$(PYTHON_DIR)/test)

PYTHON_SRC		:= $(shell ls -d $(PYTHON_DIR)/*/ | grep -v "build" | grep -v "dist" | grep -v $(PROJECT) | grep -v "test")
PYTHON_SRC      := $(patsubst $(PYTHON_DIR)/%,%,$(PYTHON_SRC))
PYTHON_SRC      := $(patsubst %/,%,$(PYTHON_SRC))

PYTHON_PROGS_IN_BIN		:= $(addprefix $(BIN_DIR)/,$(patsubst %, %_python, $(PYTHON_SRC)))
PYTHON_PREFIX           := lib/python2.7/site-packages


#### JAVA project settings



JAVA_DIR      		:=  java
JAVA_INSTALL  		:=  $(shell echo `pwd`/)java

JAVA_SRC			:= $(shell ls -d $(JAVA_DIR)/*/ )
JAVA_SRC      		:= $(patsubst $(JAVA_DIR)/%/,%,$(JAVA_SRC))

JAVA_PROGS_IN_BIN	:= $(addprefix $(BIN_DIR)/,$(patsubst %, %_java, $(JAVA_SRC)))






VPATH				:= $(SRC_DIR)  $(PYTHON_DIR) $(addprefix $(PYTHON_DIR)/, $(PYTHON_SRC)) $(JAVA_DIR) $(addprefix $(JAVA_DIR)/, $(JAVA_SRC))
FLAGS				:= -std=c++0x 


#### main entry_point of the MakeFile

#the current project does not support solutions written in Python and Java 
#all: rm_python_dirs   $(PROGS_IN_BIN) $(PYTHON_PROGS_IN_BIN) $(JAVA_PROGS_IN_BIN)
all:  $(PROGS_IN_BIN) 


#### Specific settings  for C/C++ executables
DEPENDENCE.Feature		      :=  
FLAGS.Feature			      := 
DEPENDENCE.FeatureFixed	  	  := $(INC_DIR)/Serialization.h $(INC_DIR)/Serialization.cc 
FLAGS.FeatureFixed			  := 
DEPENDENCE.KahanSum		      := $(INC_DIR)/Sum.h $(INC_DIR)/CpuTime.h
FLAGS.KahanSum			      := 





#### Specific setting for python executables
DEPENDENCE.ProblemA_python	      := DEPENDENCE.ProblemA_python


DEPENDENCE.ProblemB_python:
	cd $(PYTHON_DIR) ; python setup.py test --test-suite='ProblemA.suite';

	

#### To clear python directories

rm_python_dirs:
	- rm -r $(shell echo `pwd`/$(PYTHON_DIR))/dist
	- rm -r $(shell echo `pwd`/$(PYTHON_DIR))/build
	- rm -r $(shell echo `pwd`/$(PYTHON_DIR))/$(PROJECT).egg-info
	- rm -r $(shell echo `pwd`/$(PYTHON_DIR))/test


define make-goal
$(BIN_DIR)/$1: $2 $3 ${DEPENDENCE.${1}}
	$(CXX) $(INCLUDES) $(CPPFLAGS) $(FLAGS)  ${FLAGS.${1}} $$< ${DEPENDENCE.${1}}   -o $$@ 
endef



define make-goal-python
$(BIN_DIR)/$1: $2 ${DEPENDENCE.${1}}
	cd $(PYTHON_DIR);  python setup.py bdist_egg;
	mkdir -p $(PYTHON_INSTALL)/$(PYTHON_PREFIX)
	sudo  sh -c "export PYTHONPATH=$(PYTHON_INSTALL)/$(PYTHON_PREFIX):${PYTHONPATH};\
	easy_install --install-dir=$(PYTHON_INSTALL)/$(PYTHON_PREFIX)\
	--script-dir=$(shell echo `pwd`/$(BIN_DIR)) $(shell echo `pwd`/$(PYTHON_DIR)/dist/$(PROJECT)-0.1-py2.7.egg)" 
	echo export PYTHONPATH=$(PYTHON_INSTALL)/$(PYTHON_PREFIX):${PYTHONPATH}
endef

#$(patsubst $(PYTHON_DIR)/%,%,$(PYTHON_SRC))

define make-goal-java
$(BIN_DIR)/$1: $2  ${DEPENDENCE.${1}}
	echo ${2}
	cd $(JAVA_DIR)/$(patsubst %.java,%, ${2});\
	$(JAVA) `ls *.java`;\
	echo "Name: $(PROJECT)/$(patsubst %.java,%,${2})" > MANIFEST.MF;\
	echo "Sealed: true" >> MANIFEST.MF;\
	echo "Main-Class: $(patsubst %.java,%,${2})" >> MANIFEST.MF;\
	$(JAR) -cvmf MANIFEST.MF $(patsubst %.java,%.jar,${2})    `ls *.class` ;\
	mkdir -p ${JAVA_INSTALL}; cp  $(patsubst %.java,%.jar,${2})    ${JAVA_INSTALL} ;\
	cd $(CURDIR);\
	echo "#! /bin/sh" > $(BIN_DIR)/$1
	echo "${JAVA_EXE} -jar $(patsubst %.java,%.jar,${JAVA_INSTALL}/${2})" >> $(BIN_DIR)/$1;
#	echo "${JAVA_EXE} -jar ${JAVA_INSTALL}/$(patsubst %.java,%.jar,${2})";
#	echo "#! /bin/sh " > $(BIN_DIR)/$1 ;\
#	echo "${JAVA_EXE} -jar ${JAVA_INSTALL}/$(patsubst %.java,%.jar,${2})" >> $(BIN_DIR)/$1;
endef


info:
	$(info  SOURCES:	 $(SRC))
	$(info  PROGRAMS:	 $(PROGS))
	$(info  INCLUDES:	 $(INCLUDES))
	$(info  HEADERS:	 $(HEADERS))
	$(info  PYTHON_SRC:	 $(PYTHON_SRC))
	$(info  PYTHON_INSTALL:	 $(PYTHON_INSTALL))
	$(info  PYTHON_PROGS_IN_BIN:	 $(PYTHON_PROGS_IN_BIN))
	$(info  JAVA_DIR:	 $(JAVA_DIR))
	$(info  JAVA_SRC:	 $(JAVA_SRC))
	$(info  JAVA_INSTALL:	 $(JAVA_INSTALL))
	$(info  JAVA_PROGS_IN_BIN:	 $(JAVA_PROGS_IN_BIN))

               
clean: rm_python_dirs
	- rm $(BIN_DIR)/*


$(foreach prog,$(JAVA_SRC),$(eval $(call make-goal-java,$(prog)_java,$(prog).java )))
$(foreach prog,$(PYTHON_SRC),$(eval $(call make-goal-python,$(prog)_python,$(PYTHON_DIR)/$(prog)/$(prog).py )))
$(foreach prog,$(PROGS),$(eval $(call make-goal,$(prog),$(SRC_DIR)/$(prog).cc, $(INC_DIR)/$(prog).h )))



###SVN support
makeSVN:
	 svn mkdir  $(SVNREPO)/$(PROJECT) --username $(SVNUSER) ;\

dirs2SVN:
	- for dir in $(Dirs); do \
	svn mkdir  $(SVNREPO)/$(PROJECT)/$${dir} --username $(SVNUSER) "adding $${dir}" ; \
	done;



Commit2SVN:
	 mkdir -p $(TMPDIR2SVN); \
	 cd  $(TMPDIR2SVN) ; \
	 svn co $(SVNREPO)/$(PROJECT); \
     ls ; \
     cd - ; \
     find  ./ -iname "*" | grep -v "*.svn*" | xargs -I {} install -D {}  $(TMPDIR2SVN)/$(PROJECT)/{} ; \
     cd  $(TMPDIR2SVN)/$(PROJECT)  \
	 ls ;\
	 pwd ;\
	 svn status | grep '?'   | sed 's/^.* /svn add --parents --force  --username $(SVNUSER) /' | bash ; \
	 svn ci ; \
	 cd $(CURDIR) ;\
	 rm -r  $(TMPDIR2SVN); 


##########Git support
makeGit:
	curl -u '$(GITUSER)' $(GITREPOPATH)  -d '{"name":"$(GITREPO)"}'

Commit2Git:
#	mkdir -p $(TMPDIR2GIT)/$(PROJECT) ;	cd  $(TMPDIR2GIT)/$(PROJECT) ; \
#	pwd ;
#	cd $(CURDIR) ; pwd ;
#	find  ./ -iname "*" | grep -v "*.svn*" | xargs -I {} install -D {}  $(TMPDIR2GIT)/$(PROJECT)/{} ; 
#	find  ./ -iname "*" | grep -v "*.svn*" | grep -v "*.git" | xargs -I {} cp -r {}  $(TMPDIR2GIT)/$(PROJECT) ; 
#	cd  $(TMPDIR2GIT)/$(PROJECT) ;	pwd ;
	- git init ;
	- git remote add origin git@github.com:$(GITUSER)/$(GITREPO).git ;
	- git add ./
	- git commit -m "adding to GitHub.com"
	- git pull -s recursive -X ours origin master; 
#	git push -u origin master
	- git push https://github.com/$(GITUSER)/$(GITREPO).git master    
	- rm -rf ./.git




.PHONY: all  info clean rm_python_dirs   makeSVN dirs2SVN Commit2SVN Commit2Git makeGit

