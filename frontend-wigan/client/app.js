const API_URL = "http://localhost:8080/usuarios";

// Cargar usuarios al inicio
fetchUsuarios();

// Manejo del formulario
const form = document.getElementById("usuario-form");
form.addEventListener("submit", handleFormSubmit);

// Función para obtener usuarios
async function fetchUsuarios() {
    try {
        const response = await fetch(API_URL);
        if (!response.ok) throw new Error("Error al obtener usuarios");
        const usuarios = await response.json();

        const tbody = document.querySelector("#usuarios tbody");
        tbody.innerHTML = ""; // Limpia la tabla antes de agregar los datos

        usuarios.forEach(usuario => {
            const row = document.createElement("tr");
            row.innerHTML = `
                <td>${usuario.id}</td>
                <td>${usuario.hexa}</td>
                <td>
                    <button onclick="editUsuario(${usuario.id}, '${usuario.hexa}')">Editar</button>
                    <button onclick="deleteUsuario(${usuario.id})">Eliminar</button>
                </td>
            `;
            tbody.appendChild(row);
        });
    } catch (error) {
        console.error("Error al cargar usuarios:", error);
    }
}

// Función para manejar el envío del formulario
async function handleFormSubmit(event) {
    event.preventDefault();

    const id = document.getElementById("user-id").value;
    const hexa = document.getElementById("hexa").value;

    if (id) {
        // Si hay un ID, actualiza el usuario
        await updateUsuario(id, hexa);
    } else {
        // Si no hay ID, crea un nuevo usuario
        await addUsuario(hexa);
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
    } catch (error) {
        console.error("Error al agregar usuario:", error);
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
    } catch (error) {
        console.error("Error al actualizar usuario:", error);
    }
}

// Función para eliminar un usuario
async function deleteUsuario(id) {
    try {
        const response = await fetch(`${API_URL}/${id}`, { method: "DELETE" });
        if (!response.ok) throw new Error("Error al eliminar usuario");
        fetchUsuarios(); // Recarga los usuarios
    } catch (error) {
        console.error("Error al eliminar usuario:", error);
    }
}

// Función para editar un usuario
function editUsuario(id, hexa) {
    document.getElementById("user-id").value = id; // Establece el ID en el formulario
    document.getElementById("hexa").value = hexa; // Establece el valor actual en el campo
}
