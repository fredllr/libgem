/*
Copyright 2016-2018 Frédéric Magniette
This file is part of Libgem.

Libgem is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Libgem is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Libgem.  If not, see <http://www.gnu.org/licenses/>
*/


#include "libgem.h"

//**************************** MAIN ****************************

int main(int argc,char **argv) {


  struct ufit_tree *result;
  if (argc!=6) {
    printf("usage : %s datafile dim convcrit scalecrit output\n",argv[0]);
    return -1;
  }
  int dim=atoi(argv[2]);
  double convcrit=atof(argv[3]);
  double scalecrit=atof(argv[4]);
  struct dataset *ds=new_dataset_fromfile(dim,argv[1]);
  struct graphics *gws=NULL;

  int o=-1;
  if (!strcmp(argv[5],"none"))
    o=0;
  if (!strcmp(argv[5],"summary"))
    o=1;
  if (!strcmp(argv[5],"detail"))
    o=2;
  if (o==-1) {
    printf("unknown output : %s\n",argv[3]);
    exit(1);
  }
  //printf("o=%d\n",o);

  if (o!=0)
    gws=new_graphics(dim,700,700,ds->point_min,ds->point_max); 

  if (ds==NULL) {
    printf("error reading file\n");
    return -1;
  }
  result=ufit(ds,convcrit,scalecrit,o,gws);
  print_ufit_tree(result);
  dump_gem(result->best->gem,"/tmp/ufit_res.txt");
  free_ufit_tree(result);
  free_dataset(ds);
  free_graphics(gws);
  return 1;
}
