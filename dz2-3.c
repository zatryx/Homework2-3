#include <stdio.h>
#include <stdlib.h>

int recurs(int knotnum, int** smej, int* color, int j){
	color[j] = 1;
	int ver = 1;
	for (int i = 0; i < knotnum; ++i){
		if (smej[j][i] != 0 && color[i] != 1){
			ver += recurs (knotnum, smej, color, i);
		}
	}
	return ver;
}

int main() {
	int knotnum, edgenum;

	puts("Number of your knots: ");
	scanf("%d", &knotnum);
	puts("\nNumber of your edges: ");
	scanf("%d", &edgenum);

	char* edges = (char*)malloc(edgenum * sizeof(char));
	
	char** con = (char**)malloc(knotnum * sizeof(char*));
	for (int i = 0; i < knotnum; ++i) {
		con[i] = (char*)malloc((edgenum + 1) * sizeof(char));
	}

	int** smej = (int**)malloc(knotnum * sizeof(int*));
	for (int i = 0; i < knotnum; ++i) {
		smej[i] = (int*)calloc(knotnum, sizeof(int));
	}
	

	printf("Input edges:\n");
	scanf("%s", edges);

	printf(" |%s\n", edges);
	for (int i = 0; i < knotnum; i++) {
		printf("%d|", i);
		scanf("%s", con[i]);
	}
	FILE* file = fopen("graph.gv", "w");
	fputs("graph yesss{\n", file);
	for (int i = 0; i < knotnum; i++)
		fprintf(file, "\t%d;\n", i);
	for (int i = 0; i < edgenum; i++) {// по столбцам
		int first = -1;
		for (int j = 0; j < knotnum; j++) {
			if (con[j][i] == '1' && first == -1) {
				fprintf(file, "\t%d --", j);
				first = j;
				
			} else if (con[j][i] == '1' && first != -1) {
				fprintf(file, " %d[name = %c];\n", j, edges[i]);
				++smej[j][first];
				++smej[first][j];
				first = -1;
			}
		}
		if (first != -1){
			fprintf(file, " %d[name = %c];\n", first, edges[i]);
			++smej[first][first];
		}

	}
	fputs("}\n", file);

	fclose(file);
	free(edges);
	for (int i = 0; i < knotnum; ++i) {
		free(con[i]);
	}
	free(con);
	system("dot -Tpng graph.gv -otr.png");

	//3
	int ver = 0;
	int* color = (int*)calloc(knotnum, sizeof(int));
	ver = recurs (knotnum, smej, color, 0);
	printf ("ver = %d\n", ver);
	if (ver == knotnum){
		puts("\nGraph is connected");	
	}
	 else {
	 	puts("\nGraph is not connected");
	 }
	for (int i = 0; i < knotnum; ++i) {
		free(smej[i]);
	}
	free(smej);
	free(color);
	return 0;
}
