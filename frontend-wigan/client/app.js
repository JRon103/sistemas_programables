const API_URL = "http://34.44.90.188:8080/usuarios";

// Cargar usuarios al inicio
fetchUsuarios();

// Configuración para escuchar eventos en tiempo real
//initializeRealTimeEvents();

// Manejo del formulario
const form = document.getElementById("usuario-form");
form.addEventListener("submit", handleFormSubmit);

// Función para obtener usuarios
async function fetchUsuarios() {
    try {
        console.log("Cargando usuarios...");
        const response = await fetch(API_URL);
        if (!response.ok) throw new Error("Error al obtener usuarios");
        const usuarios = await response.json();
        console.log("Usuarios cargados:", usuarios);

        const tbody = document.querySelector("#usuarios tbody");
        tbody.innerHTML = ""; // Limpia la tabla antes de agregar los datos

        if (usuarios.length === 0) {
            displayMessage("No se encontraron usuarios", "orange");
        }

        usuarios.forEach(usuario => {
            const row = document.createElement("tr");
            row.innerHTML = `
                <td>${usuario.id}</td>
                <td>${usuario.hexa}</td>
                <td>
                    <button class="secondary" onclick="editUsuario(${usuario.id}, '${usuario.hexa}')">Editar</button>
                    <button  class="delete" onclick="deleteUsuario(${usuario.id})">Eliminar</button>
                </td>
            `;
            tbody.appendChild(row);
        });
    } catch (error) {
        console.error("Error al cargar usuarios:", error);
        displayMessage("Error al cargar usuarios: " + error.message, "red");
    }
}

// Función para editar un usuario
function editUsuario(id, hexa) {
    console.log(`Editando usuario: ${id}, ${hexa}`);
    document.getElementById("user-id").value = id; // Establece el ID en el formulario
    document.getElementById("hexa").value = hexa; // Establece el valor actual en el campo
}

// Función para mostrar mensajes en el contenedor
function displayMessage(message, color) {
    const mensajes = document.getElementById("mensajes");
    const nuevoMensaje = document.createElement("p");
    nuevoMensaje.textContent = message;
    nuevoMensaje.style.color = color;
    mensajes.appendChild(nuevoMensaje);
    console.log(`Mensaje mostrado: ${message}`);
}

// Inicializar eventos en tiempo real
function initializeRealTimeEvents() {
    const eventSource = new EventSource("http://34.44.90.188:8080/usuarios/events");
    const mensajes = document.getElementById("mensajes");

    eventSource.onopen = function () {
        console.log("Conexión establecida para eventos en tiempo real.");
    };

    eventSource.onmessage = function (event) {
        console.log("Mensaje de evento recibido:", event.data);
        const nuevoMensaje = document.createElement("p");
        nuevoMensaje.textContent = event.data; // Mostrar el mensaje recibido
        mensajes.appendChild(nuevoMensaje);

        if (mensajes) {
            mensajes.scrollTop = mensajes.scrollHeight; // Scroll automático
        }
    };

    eventSource.onerror = function (error) {
        console.error("Error al conectar con el servidor para eventos en tiempo real:", error);
        if (eventSource.readyState === EventSource.CLOSED) {
            console.log("Intentando reconectar...");
        }
    };
}

// Función para manejar el envío del formulario
async function handleFormSubmit(event) {
    event.preventDefault();
    const id = document.getElementById("user-id").value;
    const hexa = document.getElementById("hexa").value;
    if (id) {
        await updateUsuario(id, hexa); // Actualiza el usuario
    } else {
        await addUsuario(hexa); // Crea un nuevo usuario
    }
    form.reset(); // Limpia el formulario
    fetchUsuarios(); // Recarga los usuarios
}
// Función para crear un nuevo usuario
async function addUsuario(hexa) {
    try {
        const response = await fetch(API_URL, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ hexa })
        });
        if (!response.ok) throw new Error("Error al agregar usuario");
        displayMessage("Usuario agregado exitosamente.", "green");
    } catch (error) {
        console.error("Error al agregar usuario:", error);
        displayMessage("Error al agregar usuario: " + error.message, "red");
    }
}
// Función para actualizar un usuario
async function updateUsuario(id, hexa) {
    try {
        const response = await fetch(`${API_URL}/${id}`, {
            method: "PUT",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ hexa })
        });
        if (!response.ok) throw new Error("Error al actualizar usuario");
        displayMessage("Usuario actualizado exitosamente.", "green");
    } catch (error) {
        console.error("Error al actualizar usuario:", error);
        displayMessage("Error al actualizar usuario: " + error.message, "red");
    }
}
// Función para eliminar un usuario
async function deleteUsuario(id) {
    try {
        const response = await fetch(`${API_URL}/${id}`, { method: "DELETE" });
        if (!response.ok) throw new Error("Error al eliminar usuario");
        fetchUsuarios(); // Recarga los usuarios
        displayMessage("Usuario eliminado exitosamente.", "green");
    } catch (error) {
        console.error("Error al eliminar usuario:", error);
        displayMessage("Error al eliminar usuario: " + error.message, "red");
    }
}



// Función para mostrar mensajes en el contenedor
function displayMessage(message, color) {
    const mensajes = document.getElementById("mensajes");
    const nuevoMensaje = document.createElement("p");
    nuevoMensaje.textContent = message;
    nuevoMensaje.style.color = color;
    mensajes.appendChild(nuevoMensaje);
}
