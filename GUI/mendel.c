#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "mendel.h"

GtkWidget       *windowInitialKnapsack;
GtkWidget 			*windowTableData;
GtkWidget       *windowFinalTable;
GtkWidget       *windowsParentsData;
GtkWidget       ***tableData;
GtkWidget       ***tableFinalData;
GtkWidget 			*g_tableData;
GtkWidget       *g_tableFinalData;
GtkWidget       *g_frame_manualEntry;
GtkWidget       *g_frame_fileEntry;
GtkWidget       *g_filechooser_btn;
GtkWidget 			*g_entry_knapsackCapacity;
GtkWidget 			*g_entry_totalObjects;
GtkWidget 			*g_entry_fileName;
GtkWidget 			*g_scrolledwindow_initialTableData;
GtkWidget       *g_scrolledwindow_finalTable;
GtkWidget       *g_scrolledwindow_optimalSolution;
GtkWidget       *g_scrolledwindow_itemValue;
GtkWidget       *g_scrolledwindow_itemCost;
GtkWidget       *g_scrolledwindows_parents;
GtkWidget       *g_scrolledwindow_parentsData1;
GtkWidget       *g_scrolledwindows_first;
GtkWidget       *g_scrolledwindows_second;
int tableSide;
FILE 						*file_tableData;

const char *alphabet[27]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","Ñ","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
const char *alphabet_min[27]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
const char *rowHeader[4] = {"Gen Dominante","Descripción","Gen Recesivo","Descripción"};


int totalCharacteristic = 0;





dataInformation poolInitial[27];

int main() {
    GtkBuilder      *builder;
    /*--- CSS -----------------*/
    GtkCssProvider  *provider;
    GdkDisplay      *display;
    GdkScreen       *screen;
    /*-------------------------*/


    gtk_init(NULL, NULL);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "mendel.glade", NULL);

    windowInitialKnapsack = GTK_WIDGET(gtk_builder_get_object(builder, "window_initial_knapsack"));
    gtk_builder_connect_signals(builder, NULL);

    windowTableData = GTK_WIDGET(gtk_builder_get_object(builder, "window_tableData"));
    gtk_builder_connect_signals(builder, NULL);

    windowsParentsData =  GTK_WIDGET(gtk_builder_get_object(builder, "window_progenitors"));
    gtk_builder_connect_signals(builder, NULL);

    windowFinalTable = GTK_WIDGET(gtk_builder_get_object(builder, "window_finalTable"));
 gtk_builder_connect_signals(builder, NULL);
 g_scrolledwindow_finalTable = GTK_WIDGET(gtk_builder_get_object(builder, "scrolledwindow_finalTable"));

    g_scrolledwindow_initialTableData = GTK_WIDGET(gtk_builder_get_object(builder, "scrolledwindow_initialTableData"));

    g_scrolledwindows_parents = GTK_WIDGET(gtk_builder_get_object(builder, "scrolledwindow_parentsData"));
    g_scrolledwindow_parentsData1 = GTK_WIDGET(gtk_builder_get_object(builder, "scrolledwindow_parentsData1"));
    g_scrolledwindows_first = GTK_WIDGET(gtk_builder_get_object(builder, "entry_FirstParent"));
    g_scrolledwindows_second = GTK_WIDGET(gtk_builder_get_object(builder, "entry_SecondParent"));

    g_frame_fileEntry = GTK_WIDGET(gtk_builder_get_object(builder, "frame_fileEntry"));
    gtk_widget_hide(g_frame_fileEntry);
    g_frame_manualEntry = GTK_WIDGET(gtk_builder_get_object(builder, "frame_manualEntry"));
    gtk_widget_hide(g_frame_manualEntry);

    g_filechooser_btn = GTK_WIDGET(gtk_builder_get_object(builder, "filechooser_btn"));

    g_entry_knapsackCapacity = GTK_WIDGET(gtk_builder_get_object(builder, "entry_knapsackCapacity"));

    g_entry_totalObjects = GTK_WIDGET(gtk_builder_get_object(builder, "entry_totalObjects"));

    g_entry_fileName = GTK_WIDGET(gtk_builder_get_object(builder, "entry_fileName"));




    GtkFileFilter *filter = gtk_file_filter_new ();
    gtk_file_filter_add_pattern (filter, "*.cvs");
    gtk_file_chooser_add_filter (GTK_FILE_CHOOSER(g_filechooser_btn),filter);

        g_object_unref(builder);

    gtk_widget_show(windowInitialKnapsack);
    gtk_main();

    return 0;
}



void on_window_initial_knapsack_destroy() {
	gtk_main_quit();
}

void on_window_tableData_destroy() {
  free(tableData);
	gtk_main_quit();
}

void on_window_finalTable_destroy() {
  free(tableFinalData);
  gtk_main_quit();
}

void test(GtkWidget *widget,int * num)
{
  printf("Cree un mostruo %d?\n",num);
}

void createFinalTable(char offspring[tableSide][tableSide][2 * (totalCharacteristic-1)+1],int knapsackCapacity,
char headerRow[tableSide][totalCharacteristic],char headerCol[tableSide][totalCharacteristic]) {
  tableFinalData = calloc(tableSide+1,sizeof(GtkWidget**));

    g_tableFinalData = gtk_grid_new ();
    gtk_container_add (GTK_CONTAINER (g_scrolledwindow_finalTable), g_tableFinalData);

    for(int j = 0; j < tableSide+1; j++) {
      tableFinalData[j] = calloc(tableSide+1,sizeof(GtkWidget*));
    }

    for(int row =0; row < tableSide+1; row++)
    {
      for(int column=0; column < tableSide+1; column++)
      {
        tableFinalData[row][column] = gtk_entry_new();
        gtk_entry_set_width_chars(GTK_ENTRY(tableFinalData[row][column]),knapsackCapacity);
        gtk_widget_set_sensitive(tableFinalData[row][column],FALSE);
        gtk_grid_attach (GTK_GRID (g_tableFinalData),tableFinalData[row][column] , column, row, 1, 1);
        if (column!=0 &&  row !=0){
          gtk_entry_set_text (GTK_ENTRY(tableFinalData[row][column]),offspring[row-1][column-1]);
          gtk_widget_set_name(tableFinalData[row][column],"rowHeader");
        }
        if(column!=0 && row ==0){
            gtk_entry_set_text (GTK_ENTRY(tableFinalData[row][column]),headerRow[column-1]);
            gtk_widget_set_name(tableFinalData[row][column],"rowHeader");
        }
        if (column==0 && row !=0){
          gtk_entry_set_text (GTK_ENTRY(tableFinalData[row][column]),headerCol[row-1]);
          gtk_widget_set_name(tableFinalData[row][column],"rowHeader");
        }

      }
    }

    gtk_widget_set_sensitive(tableFinalData[0][0],FALSE);
    gtk_widget_set_name(tableFinalData[0][0],"rowHeader");
    gtk_widget_show_all(windowFinalTable);

}



void btn_cross_clicked(){

  int len = strlen(gtk_entry_get_text (GTK_ENTRY(g_scrolledwindows_first)));
  char parent1[len];
  char parent2[len];
  strcpy(parent1, gtk_entry_get_text (GTK_ENTRY(g_scrolledwindows_first)));
  strcpy(parent2, gtk_entry_get_text (GTK_ENTRY(g_scrolledwindows_second)));
  tableSide= pow(2, totalCharacteristic-1);
  char row[tableSide][totalCharacteristic];
  char col[tableSide][totalCharacteristic];
  int genes = 2 * (totalCharacteristic-1);
  char offspring[tableSide][tableSide][genes+1];

  cross(parent1,parent2,totalCharacteristic-1,tableSide,row,col,genes,offspring);
  //cross(parent1,parent2,totalCharacteristic-1,tableSide,row,col,offspring);
  int counter,allele;
  for(counter = 0; counter < tableSide; counter++){
    for(allele = 0; allele <tableSide; allele++){
      //for(letter = 0; letter < n*2; letter++){
      //	putchar(offspring[counter][allele][letter]);
      //}
      printf("%s", offspring[counter][allele]);
      putchar(' ');
    }
    putchar('\n');
  }

//  printf("%s\n",row[0][0]);

  createFinalTable(offspring,genes+1,row,col);
  //gtk_widget_hide(windowTableData);
  //gtk_widget_show_now(windowFinalTable);

}





void createTableData() {

	tableData = calloc(totalCharacteristic,sizeof(GtkWidget**));

  g_tableData = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (g_scrolledwindow_initialTableData), g_tableData);

  for(int j = 0; j < totalCharacteristic; j++) {
    tableData[j] = calloc(4,sizeof(GtkWidget*));
  }

  for(int row =0; row < totalCharacteristic; row++)
  {
    for(int column=0; column < 4; column++)
    {
      tableData[row][column] = gtk_entry_new();
      gtk_entry_set_width_chars(GTK_ENTRY(tableData[row][column]),10);
      gtk_grid_attach (GTK_GRID (g_tableData),tableData[row][column] , column, row, 1, 1);
      if (row == 0 ){
        gtk_entry_set_text (GTK_ENTRY(tableData[row][column]),rowHeader[column]);
        gtk_widget_set_name(tableData[row][column],"rowHeader");
        gtk_widget_set_sensitive(tableData[row][column],FALSE);
      }
      if (column ==0 && row!=0){
        gtk_entry_set_text (GTK_ENTRY(tableData[row][column]),alphabet[row-1]);
        gtk_entry_set_max_length (GTK_ENTRY(tableData[row][column]),1);
        gtk_entry_set_input_purpose (GTK_ENTRY(tableData[row][column]),GTK_INPUT_PURPOSE_ALPHA);
        g_signal_connect(G_OBJECT(GTK_ENTRY(tableData[row][column])), "editing-done",
                     G_CALLBACK(test),6);

      }
      if (column ==2 && row!=0){
        gtk_entry_set_text (GTK_ENTRY(tableData[row][column]),alphabet_min[row-1]);
        gtk_entry_set_max_length (GTK_ENTRY(tableData[row][column]),1);
      }

      if (column == 1 || column == 3 && row != 0){
        gtk_entry_set_max_length (GTK_ENTRY(tableData[row][column]),25);
      }

    }
  }
  gtk_widget_set_sensitive(tableData[0][0],FALSE);
  gtk_widget_set_name(tableData[0][0],"rowHeader");
  gtk_widget_show_all(windowTableData);


}

void createTableDataFile(char Matriz[totalCharacteristic][4][25]){

  tableData = calloc(totalCharacteristic+1,sizeof(GtkWidget**));

  g_tableData = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (g_scrolledwindow_initialTableData), g_tableData);

  for(int j = 0; j < totalCharacteristic+1; j++) {
    tableData[j] = calloc(4,sizeof(GtkWidget*));
  }

  for(int row =0; row < totalCharacteristic+1; row++)
  {
    for(int column=0; column < 4; column++)
    {
      tableData[row][column] = gtk_entry_new();
      gtk_entry_set_width_chars(GTK_ENTRY(tableData[row][column]),25);
      gtk_grid_attach (GTK_GRID (g_tableData),tableData[row][column] , column, row, 1, 1);

      if(row==0){
        gtk_entry_set_text (GTK_ENTRY(tableData[row][column]),rowHeader[column]);
        gtk_widget_set_sensitive(tableData[0][column],FALSE);
      }

      if (row!=0) {
        gtk_entry_set_text (GTK_ENTRY(tableData[row][column]),Matriz[row-1][column]);
      }
    }
  }

  gtk_widget_set_sensitive(tableData[0][0],FALSE);
  gtk_widget_set_name(tableData[0][0],"rowHeader");
  gtk_widget_show_all(windowTableData);

}



void createFile(char *fileName) {
  file_tableData = fopen(fileName,"w+");
  for(int row = 1; row < totalCharacteristic; row++)
  {
    fprintf(file_tableData,"%s",(gtk_entry_get_text(GTK_ENTRY(tableData[row][0]))));
    fprintf(file_tableData,"%s","-");
    fprintf(file_tableData,"%s",(gtk_entry_get_text(GTK_ENTRY(tableData[row][1]))));
    fprintf(file_tableData,"%s","-");
    fprintf(file_tableData,"%s",(gtk_entry_get_text(GTK_ENTRY(tableData[row][2]))));
    fprintf(file_tableData,"%s","-");
    fprintf(file_tableData,"%s",(gtk_entry_get_text(GTK_ENTRY(tableData[row][3]))));
    fprintf(file_tableData,"%s","*");
    fprintf(file_tableData,"\n");
  }
  fclose(file_tableData);
}



void on_btn_manualEntry_clicked() {
  gtk_widget_hide(g_frame_fileEntry);
  gtk_widget_show(g_frame_manualEntry);
}

void on_btn_fileEntry_clicked() {
  gtk_widget_hide(g_frame_manualEntry);
  gtk_widget_show(g_frame_fileEntry);
}

void on_btn_getEntries_clicked() {

	int entry_totalObjects = atoi(gtk_entry_get_text (GTK_ENTRY(g_entry_totalObjects)));
	totalCharacteristic = entry_totalObjects + 1;
    createTableData();
	gtk_widget_hide(windowInitialKnapsack);
    gtk_widget_show_now(windowTableData);

}

void on_btn_getFile_clicked() {

  totalCharacteristic = countObjectsFiles (gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(g_filechooser_btn)));
  char matrizD[totalCharacteristic][4][25];
  fillTable(gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(g_filechooser_btn)),matrizD);



  createTableDataFile(matrizD);
  gtk_widget_hide(windowInitialKnapsack);
  gtk_widget_show_now(windowTableData);

}

void on_radioButtonFirst_clicked(GtkButton *button){
   const gchar *text = gtk_button_get_label (button);
   gtk_entry_set_text(GTK_ENTRY(g_scrolledwindows_first),text);
}
void on_radioButtonSecond_clicked(GtkButton *button){
   const gchar *text = gtk_button_get_label (button);
   gtk_entry_set_text(GTK_ENTRY(g_scrolledwindows_second),text);
}


void createParentsTable(int genotypeAmount,char possibleGenotypes[genotypeAmount][(2 * totalCharacteristic-1) + 1]){
  GtkWidget *radio1;
  GtkWidget *radio2;
  GtkWidget *vbox1;
  GtkWidget *vbox2;
  GSList *group1 = NULL;
  GSList *group2 = NULL;
  vbox1 = gtk_vbox_new (FALSE, 0);
  vbox2 = gtk_vbox_new (FALSE, 0);
  for (int i=0;i<genotypeAmount;i++){
    radio1 =  gtk_radio_button_new_with_label(group1, possibleGenotypes[i]);
    radio2 =  gtk_radio_button_new_with_label(group2, possibleGenotypes[i]);
    char name[9+26*(totalCharacteristic-1)];
    getFenotype(poolInitial,totalCharacteristic-1,possibleGenotypes[i],name);

    group1 = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio1));
    group2 = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio2));
    gtk_box_pack_start(GTK_BOX(vbox1), radio1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox2), radio2, FALSE, FALSE, 0);
    gtk_widget_set_tooltip_text(radio1, name);
    gtk_widget_set_tooltip_text(radio2, name);
    g_signal_connect(G_OBJECT(GTK_RADIO_BUTTON(radio1)),"clicked",G_CALLBACK(on_radioButtonFirst_clicked),radio1);
    g_signal_connect(G_OBJECT(GTK_RADIO_BUTTON(radio2)),"clicked",G_CALLBACK(on_radioButtonSecond_clicked),radio2);
    gtk_widget_show(radio1);
    gtk_widget_show(radio2);

  }

  gtk_container_add (GTK_CONTAINER (g_scrolledwindows_parents), vbox1);
  gtk_container_add (GTK_CONTAINER (g_scrolledwindow_parentsData1), vbox2);

  gtk_widget_show (vbox1);
  gtk_widget_show (vbox2);


}

void on_btn_getTableData_clicked() {
  char letter[1];
  int pos =0;
  for (int i=1;i<totalCharacteristic;i++){
    dataInformation newGen;
    strcpy(letter, gtk_entry_get_text(GTK_ENTRY(tableData[i][0])));
    strcpy(newGen.dominant, gtk_entry_get_text(GTK_ENTRY(tableData[i][1])));
    strcpy(newGen.recesive, gtk_entry_get_text(GTK_ENTRY(tableData[i][3])));
    pos = getPosition(letter,alphabet);
    newGen.letterpos = pos;

    poolInitial[i-1] = newGen;
  }

  int genotypeAmount = pow(3, totalCharacteristic-1);
  char possibleGenotypes[genotypeAmount][(2 * totalCharacteristic-1) + 1];
  generateGenotypes(poolInitial,totalCharacteristic,genotypeAmount,possibleGenotypes);

  	for(int currentGenotype = 0; currentGenotype < genotypeAmount; currentGenotype++){
  		possibleGenotypes[currentGenotype][((totalCharacteristic-1)*2)] = '\0';

  	}

    int lenName = strlen(gtk_entry_get_text (GTK_ENTRY(g_entry_fileName))) + 21;

  	char fileName[lenName];
    strcpy(fileName,"examples/");
  	strcat(fileName, gtk_entry_get_text (GTK_ENTRY(g_entry_fileName)));
    strcat(fileName, ".cvs");
    printf("%d\n",fileName);
  	createFile(fileName);

  createParentsTable(genotypeAmount,possibleGenotypes);

  gtk_widget_hide(windowTableData);
  gtk_widget_show_now(windowsParentsData);

}
