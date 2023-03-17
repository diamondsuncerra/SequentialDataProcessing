#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <string.h>

typedef struct node {
   int * timestamp;
   double * value;
   struct node * next;
   struct node * prev;
}
node_t;
typedef struct dl_list {
   node_t * head;
   node_t * tail;
   int len;
}
list_t;

node_t * init_node(int * time, double * val) {
   node_t * new_node = malloc(sizeof(node_t));

   new_node -> value = malloc(sizeof(double));
   * new_node -> value = * val;
   new_node -> timestamp = malloc(sizeof(int));
   * new_node -> timestamp = * time;
   new_node -> next = NULL;
   new_node -> prev = NULL;

   return new_node;
}
void free_node(node_t * nod) {
   free(nod -> value);
   free(nod -> timestamp);
   free(nod);
}

list_t * init_list() {
   list_t * new_list = malloc(sizeof(list_t));
   new_list -> head = NULL;
   new_list -> tail = NULL;
   new_list -> len = 0;
   return new_list;
}
void print_list(list_t * list) {
   node_t * aux = list -> head;
   printf("%d\n", list -> len);
   if (aux == NULL) {
      // Lista vida
      printf("LISTA VIDA");
      return;
   }

   while (aux != list -> tail) {
      printf("%d %.2lf\n", * aux -> timestamp, * aux -> value);
      aux = aux -> next;
   }
   printf("%d %.2lf\n", * aux -> timestamp, * aux -> value);
   aux = NULL;
}
void print_values(list_t * list) {
   node_t * nod = list -> head;
   if (nod == NULL) printf("LISTA VIDA");
   while (nod != list -> tail) {
      printf("%.2lf\n", * nod -> value);
      nod = nod -> next;
   }
   printf("%.2lf\n", * nod -> value);
}
void destroy_list(list_t * list) {
   node_t * aux;
   while (list -> len > 0) {
      aux = list -> tail;
      list -> tail = list -> tail -> prev;
      free_node(aux);
      --list -> len;
   }
   free(list);
}

int insert_node(list_t * list, int time, double val, int position) {
   if (position < 0 || position > list -> len) return -1;
   node_t * nou = init_node( & time, & val);
   if (list -> len == 0) {
      list -> head = nou;
      list -> tail = nou;
      list -> tail -> next = NULL;
      list -> head -> prev = NULL;
   } else
   if (position == 0) { // la inceput
      nou -> next = list -> head;
      list -> head -> prev = nou;
      nou -> prev = NULL;
      list -> head = nou;
   } else
   if (position == list -> len) { //la final
      nou -> prev = list -> tail;
      list -> tail -> next = nou;
      nou -> next = NULL;
      list -> tail = nou;
   } else {
      node_t * nod = list -> head;
      //ajung la nodul dinaintea pozitiei unde-l pun pe nou
      int ok = 0;
      while (ok != position - 1)
         ok++, nod = nod -> next;
      nou -> next = nod -> next;
      nou -> prev = nod;
      (nod -> next) -> prev = nou;
      nod -> next = nou;
   }
   list -> len++;
   return 0;
}
int insert_sorted_asc(list_t * list, int time, double val) {
   if (list -> len == 0) { //inserare in lista vida
      insert_node(list, time, val, 0);
   } //val se diferentiaza de campul value
   else if (val < * (list -> head -> value)) { //la inceput
      insert_node(list, time, val, 0);
   } else if (val > ( * (list -> tail -> value))) //la final
      insert_node(list, time, val, list -> len);
   else { //oriunde altundeva
      node_t * nod = list -> head;
      int ok = 1;
      while ( * (nod -> value) < val) {
         nod = nod -> next;
         ok++;
      }
      insert_node(list, time, val, ok - 1);
   }
   return 0;
}
double medie(list_t * list, node_t * nod, int m) {
   double s = 0;
   s = * nod -> value;
   node_t * prev_nod = nod; //cu asta ma duc in spate
   node_t * next_nod = nod; //cu asta ma duc in fata
   int k = m * 2 + 1;
   while (m) {
      m--;
      prev_nod = prev_nod -> prev;
      next_nod = next_nod -> next;
      s = s + * prev_nod -> value;
      s = s + * next_nod -> value;
   }
   // int k=m*2+1;
   s = s / k;
   return s;
}
double deviatia_standard(list_t * list, node_t * nod, int m, double media) {
   double s = 0;
   node_t * prev_nod = nod;
   node_t * next_nod = nod;
   s = pow( * nod -> value - media, 2);
   int k = m * 2 + 1;
   while (m) {
      m--;
      prev_nod = prev_nod -> prev;
      next_nod = next_nod -> next;
      s += pow( * prev_nod -> value - media, 2);
      s += pow( * next_nod -> value - media, 2);
   } //endwhile
   // int k=m*2+1;
   s /= k;
   s = sqrt(s);
   return s; //deviatia standard
}
double val_mediana(list_t * list, node_t * node, int time, int k) {
   //nod este centrul initial al sublistei
   //creez sublista ordonata si returnez elementul din mijloc
   list_t * List = init_list();
   node_t * nod = node;
   int m = 2;
   while (m) {
      m--;
      nod = nod -> prev;
   } //ajung la nodul de start al listei
   m = k / 2;
   while (k) {
      k--;
      insert_sorted_asc(List, time, * nod -> value);
      nod = nod -> next;
   } //endwhile
   nod = List -> head;
   while (m) {
      m--;
      nod = nod -> next;
   }
   double f = * nod -> value;
   //ELIBEREAZA SPATIU
   destroy_list(List);
   return f;
}
int frequency(list_t * list, node_t * nod) {
   if (nod == list -> head) return 0; //0->nu modific 1-> modific
   int t1 = * nod -> timestamp;
   int t2 = * nod -> prev -> timestamp;
   if (abs(t1 - t2) <= 1000 && abs(t1 - t2) >= 100) return 1;
   return 0;
}
int interval_mare(list_t * list, node_t * nod, int interval) {
   if (nod == list -> tail) return 0; //0-> nu modific 1-> modific
   int t1 = * nod -> timestamp;
   int t2 = * nod -> next -> timestamp;
   if (abs(t1 - t2) > interval) return 1;
   return 0;
}
double factor_de_scalare(list_t * right, list_t * left, int time) {
   double c = time;
   double t_left = * left -> tail -> timestamp;
   double t_right = * right -> tail -> timestamp;
   c -= t_left;
   c = c / (double)(t_right - t_left);
   return c;
}
double compute_w(double i, double k) {
   double val = pow(i / (k - 1), 2);
   int j = i;
   double Val = 0;
   val = val * 0.9 + 0.1;
   for (j = 0; j < k; j++)
      Val = Val + pow(j / (k - 1), 2) * 0.9 + 0.1;
   val = val / Val;
   return val;
}
double compute_function(double c, list_t * right, list_t * left, list_t * w) {
   double rez = 1 - c;
   node_t * l = left -> head;
   node_t * r = right -> head;
   node_t * wnode = w -> head;
   double a = 0, b = 0;
   while (l) { //toate nodurile au 3 elemente deci nu testez la fiecare
      a = a + ( * l -> value) * ( * wnode -> value);
      b = b + ( * r -> value) * ( * wnode -> value);
      l = l -> next;
      r = r -> next;
      wnode = wnode -> next;
   }
   rez = rez * a + c * b;
   return rez;
} //endfunction
void print_interval(int x, int y, int nr) {
   printf("[%d, %d] %d\n", x, y, nr);
} //endfunction

list_t * e1(list_t * list) { //adaug argumente pe parcurs
   int k = 5; // lungime sublista
   int m = k / 2;
   node_t * nod = list -> head;
   node_t * finish = list -> tail;
   int cont = 0;
   list_t * new_list = init_list(); //lista de returnat
   while (cont < m) {
      cont++;
      insert_node(new_list, * nod -> timestamp, * nod -> value, new_list -> len);
      //adaug nodurile pe care nu le iau in seama la verificare
      nod = nod -> next;
      finish = finish -> prev;
   }
   while (nod != finish -> next) {
      double media = medie(list, nod, m);
      double dev = deviatia_standard(list, nod, m, media);
      double minim = media - dev;
      double maxim = media + dev;
      int a = 0;
      if ( * nod -> value > maxim || * nod -> value < minim) a++;
      else insert_node(new_list, * nod -> timestamp, * nod -> value, new_list -> len);
      nod = nod -> next;
   }
   finish = finish -> next;
   //adaug ultimele (int)k/2 noduri din lista
   while (finish != list -> tail) {
      insert_node(new_list, * finish -> timestamp, * finish -> value, new_list -> len);
      finish = finish -> next;
   }
   insert_node(new_list, * finish -> timestamp, * finish -> value, new_list -> len);

   destroy_list(list);
   return new_list;
} //endfunction e1
list_t * e2(list_t * list) { //returnez lista creata
   list_t * new_list = init_list();
   int t, k = 5, m = 2;
   node_t * first_nod = list -> head;
   node_t * last_nod = list -> tail;
   node_t * nod;
   while (m) {
      m--;
      first_nod = first_nod -> next;
      last_nod = last_nod -> prev;
   } //vor fi extremele nodurilor pe care le iau in mijlocul sublistei
   nod = first_nod;
   m = 2;
   double v;
   while (nod != last_nod -> next) {
      t = * nod -> timestamp;
      k = 5;
      v = val_mediana(list, nod, t, k);
      insert_node(new_list, t, v, new_list -> len);
      nod = nod -> next;
   } //endwhile
   destroy_list(list);
   return new_list;
} //endfunction e2
list_t * e3(list_t * list) {
   list_t * new_list = init_list();
   node_t * first_nod = list -> head;
   node_t * last_nod = list -> tail;
   int k = 5;
   int m = k / 2;
   double media;
   while (m) {
      m--;
      first_nod = first_nod -> next;
      last_nod = last_nod -> prev;
   } //intre first si last se afla centrele ferestrelor
   m = k / 2;
   node_t * nod = first_nod;
   while (nod != last_nod -> next) {
      media = medie(list, nod, m);
      insert_node(new_list, * nod -> timestamp, media, new_list -> len);
      nod = nod -> next;
   }
   destroy_list(list);
   return new_list;
} //endfunction e3

list_t * u(list_t * list) {
   list_t * new_list = init_list();
   node_t * nod = list -> head;
   while (nod) {
      if (frequency(list, nod)) { //fac schimbari
         int t1 = * nod -> timestamp;
         int t2 = * nod -> prev -> timestamp;
         double val1 = * nod -> value;
         double val2 = * nod -> prev -> value;
         t1 = (t1 + t2) / 2;
         val1 = (val1 + val2) / 2;
         * nod -> timestamp = t1;
         * nod -> value = val1;
         insert_node(new_list, t1, val1, new_list -> len);
      } else insert_node(new_list, * nod -> timestamp, * nod -> value, new_list -> len);
      nod = nod -> next;
   }
   destroy_list(list);
   return new_list;
} //endfunction u

void c(list_t * list) {
   node_t * nod = list -> head;
   int contor = 0, alfa, k = 3, i, interval = 1000;
   double c, val;
   while (nod) {
      if (interval_mare(list, nod, interval)) {
         list_t * right = init_list();
         list_t * left = init_list();
         node_t * alt_nod = nod -> next;
         while (k) {
            k--;
            insert_node(right, * alt_nod -> timestamp, * alt_nod -> value, 0);
            alt_nod = alt_nod -> next;
         } //creeare lista right
         k = 3;
         alt_nod = nod;
         while (k) {
            k--;
            insert_node(left, * alt_nod -> timestamp, * alt_nod -> value, 0);
            alt_nod = alt_nod -> prev;
         }
         k = 3;
         list_t * w = init_list();
         //pentru usurinta w e o lista de acelasi tip doar ca timestamp ramane 0 mereu
         for (i = 0; i < k; i++) {
            if (i == 0) val = 0.07;
            else if (i == 1) val = 0.23;
            else val = 0.7;
            val = compute_w(i, k);
            insert_node(w, 0, val, w -> len); //inseram in ordine in lista w
         } //endfor creeare lista w
         int t = * nod -> timestamp;
         for (alfa = 200; t + alfa < * right -> tail -> timestamp; alfa += 200) {
            c = factor_de_scalare(right, left, t + alfa);
            double rez = compute_function(c, right, left, w);
            insert_node(list, t + alfa, rez, contor + 1);
            k = 3;
            alt_nod = nod -> next;
            contor++;
            nod = nod -> next;
         } //endfor
         destroy_list(right);
         destroy_list(left);
         destroy_list(w);
      } //endif
      nod = nod -> next;
      contor++;
   } //endwhile
} //endfunction c
void st(list_t * list, double delta) {
   int x;
   if ( * list -> head -> value >= 0)
      x = (int) * list -> head -> value;
   else x = (int) * list -> head -> value - 1;
   int contor = 0; //numara nodurile
   node_t * nod = list -> head;
   while (nod) {
      if ( * nod -> value >= x && * nod -> value <= x + delta)
         // interval bun continui sa numar
         contor++;
      else {
         // resetez numaratoarea si afisez intervalul precedent
         //  la final de tot afisez intervalul
         if (contor)
            print_interval(x, x + delta, contor);
         contor = 0;
         while ( * nod -> value >= x + delta || * nod -> value < x)
            x += delta;
         contor++;
      } //endelse
      nod = nod -> next;
   } //endwhile
   if (contor)
      print_interval(x, x + delta, contor);
} //endfunction st

int main(int argc, char ** argv) {
   list_t * list = init_list();
   int n = 0, nr = 0, i = 0, time = 0, j = 0; //n numar noduri
   double val = 0; //j tine cont de argv
   if (strstr(argv[1], "st") != NULL) { // facem cu delta
      double delta = 0;
      delta = (double) atoi(argv[1] + 4);
      //CITIRE CRESCATOARE
      scanf("%d", & n);
      for (i = 0; i < n; i++) {
         scanf("%d%lf", & time, & val);
         insert_sorted_asc(list, time, val);
      } //endfor
      st(list, delta);
   } //endif
   else {
      //CITIRE NORMALA
      scanf("%d", & n);
      for (i = 0; i < n; i++) {
         scanf("%d%lf", & time, & val);
         insert_node(list, time, val, list -> len);
      } //endfor
      for (j = 1; j < argc; j++) {
         nr = 1;
         if (strcmp(argv[j], "--e1") == 0) nr = 1;
         else if (strcmp(argv[j], "--e2") == 0) nr = 2;
         else if (strcmp(argv[j], "--e3") == 0) nr = 3;
         else if (strcmp(argv[j], "--u") == 0) nr = 4;
         else if (strcmp(argv[j], "--c") == 0) nr = 5;
         switch (nr) {
         case 1:
            list = e1(list);
            break;
         case 2:
            list = e2(list);
            break;
         case 3:
            list = e3(list);
            break;
         case 4:
            list = u(list);
            break;
         case 5:
            c(list);
            break;
         } //endswitch
         nr = 6;
      } //endfor
      print_list(list);
   } //endelse
   destroy_list(list);
   return 0;
}
