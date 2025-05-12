# C++ Notes API

A simple RESTful API for user registration, authentication, and note management, built with [Crow](https://github.com/CrowCpp/Crow) and [nlohmann/json](https://github.com/nlohmann/json).

## Features

- User registration and login with token-based authentication
- Add, retrieve, and delete personal notes
- JSON file storage for users and notes

## Endpoints

### Register

- **POST** `/register`
- **Body:**  
  ```json
  {
    "username": "your_username",
    "password": "your_password"
  }
  ```
- **Response:**  
  - `200 OK` if registered  
  - `400 Bad Request` if user exists or invalid JSON

### Login

- **POST** `/login`
- **Body:**  
  ```json
  {
    "username": "your_username",
    "password": "your_password"
  }
  ```
- **Response:**  
  - `200 OK` with token in `message`  
  - `401 Unauthorized` if credentials are invalid

### Add Note

- **POST** `/note`
- **Headers:**  
  `Authorization: Bearer <token>`
- **Body:**  
  ```json
  {
    "content": "your note content"
  }
  ```
- **Response:**  
  - `200 OK` if note added  
  - `401 Unauthorized` if not authenticated

### Get Notes

- **GET** `/note`
- **Headers:**  
  `Authorization: Bearer <token>`
- **Response:**  
  - `200 OK` with user's notes  
  - `401 Unauthorized` if not authenticated

### Delete Notes

- **DELETE** `/note`
- **Headers:**  
  `Authorization: Bearer <token>`
- **Response:**  
  - `200 OK` if notes deleted  
  - `401 Unauthorized` if not authenticated

## Data Storage

- `users.json`: Stores registered users and passwords
- `notes.json`: Stores notes with associated users

## Running

1. Build the project with Crow and nlohmann/json dependencies.
2. Run the executable. The server listens on port `18080`.

## Example Usage (with curl)

```sh
# Register
curl -X POST http://localhost:18080/register -d '{"username":"alice","password":"pass"}'

# Login
curl -X POST http://localhost:18080/login -d '{"username":"alice","password":"pass"}'

# Add Note
curl -X POST http://localhost:18080/note -H "Authorization: Bearer <token>" -d '{"content":"Hello"}'

# Get Notes
curl -X GET http://localhost:18080/note -H "Authorization: Bearer <token>"

# Delete Notes
curl -X DELETE http://localhost:18080/note -H "Authorization: Bearer <token>"
```

## License

MIT
