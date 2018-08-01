double **readMat(char *argv, int *nz, int *M, int *N){
	int rows, columns, nonZero;
	int *rowInd = NULL;
	int *colInd = NULL;
	double *value = NULL;
	FILE *fp = fopen(argv, "r");
	while(fscanf(fp,"%d", &rows) == 0)
		fscanf(fp, "%*[^\n]\n", NULL);
	fscanf(fp, "%d %d", &columns, &nonZero);
	printf("M: %d  N: %d  nz: %d\n", rows, columns, nonZero);

	rowInd = malloc(nonZero * sizeof(int));
	colInd = malloc(nonZero * sizeof(int));
	value = malloc(nonZero * sizeof(double));
	printf("Memory Allocated\n");

	for(int i = 0; i < nonZero; i++)	
		fscanf(fp, "%d %d %lf", &rowInd[i], &colInd[i], &value[i]);
	printf("Done Scanning\n");

	double **oMat = malloc(rows * sizeof(double *));
	for(int i = 0; i < rows; i++)
		oMat[i] = malloc(columns * sizeof(double));
	printf("Matrix Allocated");

	for(int i = 0; i < rows; i++)
		for(int j = 0; j < columns; j++)
			oMat[i][j] = 0;
	for(int i = 0; i < nonZero; i++)
		oMat[rowInd[i]-1][colInd[i]-1] = value[i];
	printf("Matrix Filled\n");

	free(rowInd);
	free(colInd);
	free(value);

	fclose(fp);
	printf("Completed\n");

	return(oMat);
}
