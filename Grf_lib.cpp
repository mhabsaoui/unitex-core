/*
 * Unitex
 *
 * Copyright (C) 2001-2011 Université Paris-Est Marne-la-Vallée <unitex@univ-mlv.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

#include <stdlib.h>
#include "Grf_lib.h"
#include "Error.h"
#include "Ustring.h"


/**
 * Creates an empty grf object.
 */
Grf* new_Grf() {
Grf* grf=(Grf*)malloc(sizeof(Grf));
if (grf==NULL) fatal_alloc_error("new_Grf");
grf->size[0]='\0';
grf->font[0]='\0';
grf->ofont[0]='\0';
grf->bcolor[0]='\0';
grf->fcolor[0]='\0';
grf->acolor[0]='\0';
grf->scolor[0]='\0';
grf->ccolor[0]='\0';
grf->dboxes[0]='\0';
grf->dframe[0]='\0';
grf->ddate[0]='\0';
grf->dfile[0]='\0';
grf->ddir[0]='\0';
grf->drig[0]='\0';
grf->drst[0]='\0';
grf->fits[0]='\0';
grf->porient[0]='\0';
grf->n_states=0;
grf->states=NULL;
return grf;
}


/**
 * Creates an empty grf state.
 */
GrfState* new_GrfState() {
GrfState* s=(GrfState*)malloc(sizeof(GrfState));
if (s==NULL) fatal_alloc_error("new_GrfState");
s->box_content=NULL;
return s;
}


/**
 * Frees all the memory associated to the given grf state.
 */
void free_GrfState(GrfState* s) {
if (s==NULL) return;
free(s->box_content);
free(s->transitions);
free(s);
}


/**
 * Frees all the memory associated to the given grf.
 */
void free_Grf(Grf* grf) {
if (grf==NULL) return;
for (int i=0;i<grf->n_states;i++) {
	free_GrfState(grf->states[i]);
}
free(grf->states);
free(grf);
}


/**
 * Reads a line and stores it into the destination string. Returns 1
 * in case of success; 0 otherwise.
 */
static int read_grf_header_line(U_FILE* f,Ustring* line,unichar* dest) {
if (!readline(line,f)) return 0;
chomp_new_line(line);
if (line->len > GRF_HEADER_LINE_SIZE) return 0;
u_strcpy(dest,line->str);
return 1;
}


/**
 * Reads a line containing a number and stores it into *n. Returns 1
 * in case of success; 0 otherwise.
 */
static int read_grf_n_states(U_FILE* f,Ustring* line,int *n) {
if (!readline(line,f)) return 0;
return 1==u_sscanf(line->str,"%d",n);
}


/**
 * Reads a line containing a grf state. Returns 1 in case of success;
 * 0 otherwise.
 */
static int read_grf_state(U_FILE* f,Ustring* line,int n,Grf* grf) {
if (!readline(line,f) || line->len < 2) return 0;
unsigned int pos=0;
if (line->str[pos]=='s') {
	/* Old stuff: s at line start used to mean that the box was selected.
	 * We can ignore this */
	pos++;
}
if (line->str[pos]!='"') return 0;
unsigned int start_pos=pos;
pos++;
while (pos<line->len && line->str[pos]!='"') {
	if (line->str[pos]=='\\') pos++;
	pos++;
}
if (++pos>=line->len) {
	/* Reached the end of line ? It's an error. We use a ++ since
	 * a valid grf line should always have a space after the box content */
	return 0;
}
unichar c=line->str[pos];
if (c!=' ') return 0;
line->str[pos]='\0';
grf->states[n]=new_GrfState();
grf->states[n]->box_content=u_strdup(line->str+start_pos);
pos++;
int shift;
if (3!=u_sscanf(line->str+pos,"%d%d%d%n",
		&(grf->states[n]->x),
		&(grf->states[n]->y),
		&(grf->states[n]->n_transitions),
		&shift)) return 0;
pos=pos+shift;
grf->states[n]->transitions=(int*)malloc(grf->states[n]->n_transitions*sizeof(int));
if (grf->states[n]->transitions==NULL) return 0;
for (int i=0;i<grf->states[n]->n_transitions;i++) {
	if (1!=u_sscanf(line->str+pos,"%d%n",
			&(grf->states[n]->transitions[i]),
			&shift)) return 0;
	pos=pos+shift;
}
return 1;
}


/**
 * Loads and returns a grf file, or NULL in case of error.
 */
Grf* load_grf(char* name) {
U_FILE* f=u_fopen_existing_versatile_encoding(DEFAULT_MASK_ENCODING_COMPATIBILITY_INPUT,name,U_READ);
if (f==NULL) return NULL;
Ustring* line=new_Ustring();
Grf* grf=new_Grf();
if (!readline(line,f) || u_strcmp(line->str,"#Unigraph\n")) goto error;
if (!read_grf_header_line(f,line,grf->size)) goto error;
if (!read_grf_header_line(f,line,grf->font)) goto error;
if (!read_grf_header_line(f,line,grf->ofont)) goto error;
if (!read_grf_header_line(f,line,grf->bcolor)) goto error;
if (!read_grf_header_line(f,line,grf->fcolor)) goto error;
if (!read_grf_header_line(f,line,grf->acolor)) goto error;
if (!read_grf_header_line(f,line,grf->scolor)) goto error;
if (!read_grf_header_line(f,line,grf->ccolor)) goto error;
if (!read_grf_header_line(f,line,grf->dboxes)) goto error;
if (!read_grf_header_line(f,line,grf->dframe)) goto error;
if (!read_grf_header_line(f,line,grf->ddate)) goto error;
if (!read_grf_header_line(f,line,grf->dfile)) goto error;
if (!read_grf_header_line(f,line,grf->ddir)) goto error;
if (!read_grf_header_line(f,line,grf->drig)) goto error;
if (!read_grf_header_line(f,line,grf->drst)) goto error;
if (!read_grf_header_line(f,line,grf->fits)) goto error;
if (!read_grf_header_line(f,line,grf->porient)) goto error;
if (!readline(line,f) || u_strcmp(line->str,"#\n")) goto error;
if (!read_grf_n_states(f,line,&(grf->n_states))) goto error;
grf->states=(GrfState**)calloc(grf->n_states,sizeof(GrfState*));
if (grf->states==NULL) {
	fatal_alloc_error("load_Grf");
}
for (int i=0;i<grf->n_states;i++) {
	if (!read_grf_state(f,line,i,grf)) goto error;
}
goto end;
error:
free_Grf(grf);
grf=NULL;
end:
free_Ustring(line);
return grf;
}


/**
 * Saves the given grf to the given file.
 *
 * Note that if the output is the standard output, we have to add the
 * BOM character so that redirecting the output to a file produces a valid
 * UTF16LE grf. We also force the encoding to UTF16LE.
 */
void save_grf(U_FILE* f,Grf* grf) {
if (f==U_STDOUT) {
	f->enc=UTF16_LE;
	u_fputc(U_BYTE_ORDER_MARK,f);
}
u_fprintf(f,"#Unigraph\n");
u_fprintf(f,"%S\n",grf->size);
u_fprintf(f,"%S\n",grf->font);
u_fprintf(f,"%S\n",grf->ofont);
u_fprintf(f,"%S\n",grf->bcolor);
u_fprintf(f,"%S\n",grf->fcolor);
u_fprintf(f,"%S\n",grf->acolor);
u_fprintf(f,"%S\n",grf->scolor);
u_fprintf(f,"%S\n",grf->ccolor);
u_fprintf(f,"%S\n",grf->dboxes);
u_fprintf(f,"%S\n",grf->dframe);
u_fprintf(f,"%S\n",grf->ddate);
u_fprintf(f,"%S\n",grf->dfile);
u_fprintf(f,"%S\n",grf->ddir);
u_fprintf(f,"%S\n",grf->drig);
u_fprintf(f,"%S\n",grf->drst);
u_fprintf(f,"%S\n",grf->fits);
u_fprintf(f,"%S\n",grf->porient);
u_fprintf(f,"#\n");
u_fprintf(f,"%d\n",grf->n_states);
for (int i=0;i<grf->n_states;i++) {
	u_fprintf(f,"%S %d %d %d ",grf->states[i]->box_content,grf->states[i]->x,grf->states[i]->y,
			grf->states[i]->n_transitions);
	for (int j=0;j<grf->states[i]->n_transitions;j++) {
		u_fprintf(f,"%d ",grf->states[i]->transitions[j]);
	}
	u_fprintf(f,"\n");
}
}


/**
 * Returns a copy of the given grf state.
 */
GrfState* cpy_grf_state(GrfState* s) {
if (s==NULL) return NULL;
GrfState* res=new_GrfState();
res->box_content=u_strdup(s->box_content);
res->x=s->x;
res->y=s->y;
res->n_transitions=s->n_transitions;
res->transitions=(int*)malloc(res->n_transitions*sizeof(int));
if (res->transitions==NULL) fatal_alloc_error("cpy_grf_state");
memcpy(res->transitions,s->transitions,res->n_transitions*sizeof(int));
return res;
}