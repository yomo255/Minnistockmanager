//librerías

#include "termicolor.h" //Libreria creada por mi para colorear la terminal usando ANSI color codes.
#include <iostream> //Libreria para input, output stream
#include <string> //libreria para variables tipo string y sus funciones
#include <limits> //libreria que utilizamos para limpiar la cantidad maxima de una linea de el buffer
#include <iomanip> //libreria que utilizo para las funciones "Fixed", "Setprecision(), left y setw()".
#include <vector> //libreria para la creacion de arrays tipo vector
#include <cctype> //libreria que utilizamos para la funcion tolower.
#include <fstream> //Libreria que usamos para crear el archivo de texto.
using namespace std; //Evita tener que escribir std al inicio de cada linea que forme parta de el standard.
using namespace termicolor;//Evita tener que escribir termicolor para usar mi libreria

//Variables globales
int globalID = 1;

//Estructura del producto --Jessed
struct product {
    float productPrice; //Variable tipo float para el precio del producto
    int productQuantity; //Variable tipo Int para la cantidad de productos en stock.
    string productName; //Variable tipo String para el nombre del producto.
    int productID; //Variable para crear el id del producto.
}; //cierra la estructura (Siempre debe haber un ;)

//función para la creación del producto --Jessed
product createProduct() { //Crea una función (fabrica)
    product p; // crea un producto vacío
    cout << purple << "[+] Product name: " << reset; // Pide el nombre del producto 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Limpia el buffer
    getline(cin, p.productName); // le asigna un nombre al producto
    cout << blue << "[$] Price: "; // pide el precio del producto
    cin >> p.productPrice; // le asigna valor al producto
    cout << purple << "[#] Quantity: "; //pide el stock de el producto
    cin >> p.productQuantity; //asigna cantidad de productos en stock
    cout << "Product ID: ";
    p.productID = globalID; //Le asigna el valor de globalID a product ID.
    globalID++;
    cout << p.productID << "\n"; //Le asigna un ID unico.
    return p; // devuelve el producto lleno
}

//Me cree esta funcion pa no estar repitiendo 5 lineas cada vez que quiera hacer una validacion de datos.
void errorMessage() { //Void es basicamente que no tiene valor. En otras palabras un vacio.
    cout << red << "\nInvalid Input\n" << reset;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
}

int main() { //inicio del bloque de código principal

int menu;
int numProducts; //Variable asignable a la cantidad de productos que serán creados
vector<product> inventory; //array de vectores para el inventario
char confirm;//Variable tipo char utilizada para confirmar una acción.
bool menuLoop = true; //Mantiene el loop funcionando hasta que este se apague.
const int minStock = 0;

//Menu -- Yomar
//Uso de ANSI color codes en todo el código -- Jessed 
while (menuLoop)
{
    float totalInventory = 0.0;//variable asignable tipo float al valor total del inventario.
cout << "\n" << blue << "========== MINI STOCK MANAGER ==========" << reset << "\n"; //Menu
cout << purple << "1. Add products\n";
cout << "2. View inventory\n";
cout << "3. Edit product\n";
cout << "4. Exit\n" << reset;
cout << blue <<  "========================================\n";
cout << "Select an option: " << reset;

if (!(cin >> menu)){//Valida si la opción ingresada es valida.
    errorMessage();
    continue;
}

switch (menu)
{
    //Crear producto -- Jessed
case 1:
    cout << green << "\n============= Add Products =============\n" << reset;

    cout << blue <<  "How many products do you want to add?\n" << reset;//Pregunta cuantos productos desea ingresar
    cin.clear();
    cin >> numProducts;//Ingresa valor a numProducts

    if (numProducts <= minStock) {
        cout << yellow << "You must create one or more products.\n\n" << reset; //Mensaje de error por si pone números negativos o cero
        break;
    } else {
    for (int i = 0; i < numProducts; i++) {//inicia ciclo for para la creación de un producto
        cout << green <<"\n--- Product #" << (i + 1) << "\n";
        product p = createProduct();//Llama a la función anteriormente creada
        inventory.push_back(p);//Ingresa el producto dentro de el inventario.
        cout << "Saved to inventory, current size: " << inventory.size() << "\n";//Imprime cuantos productos tiene el inventario en ese momento.
        }
    }

    break;

case 2:
    //Inventario --Yomar, Jessed
    cout << blue << "\n=============== INVENTORY ==============\n\n" << reset;
        cout << purple << left << setw(6) << "ID" << setw(18) << "Product" << setw(10) << "Price" << setw(10) << "Stock"
        << setw(12) << "Subtotal" << "\n" << reset;
    for (auto& item : inventory) { //Inicia ciclo for para imprimir el inventario.
    float subtotal = item.productPrice * item.productQuantity; //declara una variable tipo float para saber cuanto vale el stock de cada objeto.
    cout << left << setw(6) << item.productID << setw(18) << item.productName << setw(10) << fixed << setprecision(2) << item.productPrice
    << setw(10) << item.productQuantity << setw(12) << fixed << setprecision(2) << subtotal << "\n" << reset; //Imprime el inventario

    totalInventory += subtotal;//Calcula el valor del inventario conjunto
    }
    cout << blue << "\nTOTAL INVENTORY VALUE: " << fixed << setprecision(2) << totalInventory << "$\n" << reset;//Imprime el valor del inventario conjunto
    
    cout << purple << "Do you want to [1] create an inventory file or [2] return to the main menu?\n" << reset;//Pregunta al usuario si desea guardar el inventario en un archivo de texto
    
    if (!(cin >> menu)) {
        errorMessage();
        continue;
    }

    // Crear archivo txt que contenga el inventario -- Yomar
    if (menu == 1) {
        ofstream createFile("Inventory.txt"); //Abre el archivo!
        if (!createFile) { //Esto básicamente es que si createFile = False, da un mensaje de error. La vdd nunca me ha dado error pero por si acaso!
            cout << red <<"Error creating file.\n" << reset; //Imprime un mensaje de error en caso de ocurrir un error a la hora de crear el archivo.
            break;
        }
        createFile << left << setw(6) << "ID" << setw(18) << "Product" << setw(10) << "Price"
            << setw(10) << "Stock" << setw(12) << "Subtotal" << "\n";
            for (auto& item : inventory) {
                float subtotal = item.productPrice * item.productQuantity;
                    createFile << left << setw(6) << item.productID << setw(18) << item.productName << setw(10) << fixed << setprecision(2) << item.productPrice
            << setw(10) << item.productQuantity << setw(12) << fixed << setprecision(2) << subtotal << "\n"; //Imprime el inventario
            }
            createFile.close(); //Cierra el archivo (Sin esto no guarda el archivo asi que no lo toquen!!!)
            cout << green << "\nFile saved successfully!\n" << reset;

    } else if (menu == 2) {
        cout << yellow << "\nReturning to main menu...\n" << reset;
        break; //break pa que te devuelva al menu
    }
    break; // Break del case

    //Editar producto -- Gabriel
case 3: {
cout << green << "\n============= Edit Product =============\n" << reset;//Inicia la sección de edición de productos
cout << blue << "Which product do you want to edit? (Enter the product name... ) \n" << reset;
cout << blue << "Product ID: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
int edit;
if (!(cin >> edit)) {
    errorMessage();
    continue;
}
bool searching = false;
cout << reset;

cout << green << "\nSEARCHING FOR "<<edit<<"...\n"; //flavor text
for (auto& item : inventory) {if (item.productID == edit){searching=true;
cout<< green <<"Found Product "<<item.productName <<"!"<< "\n\nDo you wish to edit ALL data? (Y/N): " << reset;
char all;
cin>>all;//obv ps le da la opción a borrar el producto entero o no 
all = tolower(all); //tolower funciona para convertir la opción seleccionada a minúscula.

if (all == 'y'){
    product edited = createProduct();
    swap (item, edited);}
//Gabriel D solution (sunglasses emoji), si el usuario quiere cambiar el producto por completo,
//entonces, crea otro producto y SWAP los contenidos de el que ya existe!!!!!111!!!!111!!!
else if (all == 'n'){

    cout<< purple << "[+] Enter the new name for the product (or press the 'ENTER' key for the same name): " << reset;
    string namenuevo;
    cin.ignore();
    if (!(getline(cin,namenuevo))) {
        errorMessage();
        continue;
    }
    if (!namenuevo.empty()) item.productName = namenuevo;

    cout<< blue <<"[$] Enter the new price for the product (or enter 0 to keep the same price): " << reset;
    float pricenuevi;
    if (!(cin >> pricenuevi)) {
        errorMessage();
        continue;
    }
    if (pricenuevi > 0) item.productPrice = pricenuevi;

    cout<< purple << "[#] Enter the quantity in stock for this new product (or type -1 for the same quantity): " << reset;
    //-1 para el mismo amount para que puedan entrar 0 (as in they have none)
    int amountnuez;
    if (!(cin >> amountnuez)) {
        errorMessage();
        continue;
    }
    if (amountnuez>=0) item.productQuantity = amountnuez;
cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear el buffer porsiaca
}

cout<< green <<"\nProduct updated!\n" << reset;
break; //este break acaba el for
}

}
if (!searching) {
    cout<< red <<"\nProduct not found.\n" << reset;}
    break; //este break es pal case como tal
}
// opción Exit -- Jessed
case 4:
// Confirmación de salida
while (menuLoop) {
    cout << yellow << "Do you really want to QUIT? (Y/N): " << reset;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!(cin >> confirm)) {
        errorMessage();
        continue;
    }
      confirm = tolower(confirm); //Tolower para convertir la letra seleccionada a minúscula.
    if (confirm == 'y') {
        cout << green << "\nThanks for using 'MiniStockManager', see you next time!\n\n" << reset;
        menuLoop = false;
        break;
    } else if (confirm == 'n') {
        cout << yellow <<"Returning to the menu...\n\n" << reset; //Reinicia el loop y te devuelve al menu
        break;
    } else {
        cout << red <<"Invalid input...\n\n" << reset; //En caso de que ponga una opción que no sea valida. 
        continue;
    }
}
//Si ingresa una opcion incorrecta
default:
if (menu >= 5) {
errorMessage();
    break;
        }
    }
}
return 0;
}