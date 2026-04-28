This is the Readme file for the Web interface. The original code written to understand the concepts of linked list through this project is in the folder Original_code_in_CPP inside the main folder.

Run the following two commands in the terminal of Original_code_in_CPP folder to see the execution of code in cpp :-

1. g++ Raw_code.cpp -o program
2. .\program


# 👥 Social Media Friend List App

A full-stack web application that replicates the logic of a **C-language linked-list friend manager** — migrated to a modern stack with Node.js, Express, PostgreSQL, and a dark-themed browser UI.

---

## 🧠 Concept

The original C program maintained an in-memory singly linked list with three core operations:

| C Function | Web Equivalent | SQL |
|---|---|---|
| `addFriend()` | `POST /friends` | `INSERT INTO friends` |
| `removeFriend()` | `DELETE /friends/:name` | `DELETE WHERE name = $1` |
| `displayFriends()` | `GET /friends` | `SELECT * ORDER BY id ASC` |

---

## 🛠️ Tech Stack

| Layer | Technology |
|---|---|
| Frontend | HTML / CSS / Vanilla JavaScript |
| Backend | Node.js + Express.js |
| Database | PostgreSQL |
| DB Driver | node-postgres (`pg`) |
| Dev Tool | nodemon |

---

## 📁 Project Structure

```
friend-app/
├── backend/
│   ├── server.js          # Express REST API
│   ├── package.json
│   ├── .env               # ❌ NOT committed (secrets)
│   └── .env.example       # ✅ Safe template
├── frontend/
│   └── index.html         # Single-page UI
└── .gitignore
```

---

## ⚙️ Setup & Installation

### Prerequisites
- [Node.js](https://nodejs.org) v18+
- [PostgreSQL](https://www.postgresql.org/download) v14+

### 1. Clone the Repository
```bash
git clone https://github.com/your-username/friend-app.git
cd friend-app
```

### 2. Create the Database
```sql
-- In your PostgreSQL terminal (psql)
CREATE DATABASE friendsdb;
```

### 3. Configure Environment Variables
```bash
# Copy the example file
cp backend/.env.example backend/.env
```

Then open `backend/.env` and fill in your real values:
```env
DB_HOST=localhost
DB_PORT=5432
DB_NAME=friendsdb
DB_USER=postgres
DB_PASSWORD=your_real_password_here
PORT=3001
```

### 4. Install Dependencies & Start Backend
```bash
cd backend
npm install
npm run dev
```

You should see:
```
✅ Table ready
🚀 Server running on http://localhost:3001
```

> The `friends` table is **auto-created** on first run — no manual SQL needed.

### 5. Open the Frontend
Simply open `frontend/index.html` in your browser.

> No build step needed — pure HTML/CSS/JS.

---

## 🔌 REST API Reference

### Get All Friends
```http
GET /friends
```
**Response:**
```json
[
  { "id": 1, "name": "Alice", "added_at": "2025-01-01T10:00:00.000Z" },
  { "id": 2, "name": "Bob",   "added_at": "2025-01-01T10:05:00.000Z" }
]
```

### Add a Friend
```http
POST /friends
Content-Type: application/json

{ "name": "Charlie" }
```
**Response:** `201 Created`
```json
{ "id": 3, "name": "Charlie", "added_at": "2025-01-01T10:10:00.000Z" }
```

### Remove a Friend
```http
DELETE /friends/Charlie
```
**Response:** `200 OK`
```json
{ "message": "Friend removed successfully." }
```

---

## 🗄️ Database Schema

```sql
CREATE TABLE friends (
    id        SERIAL        PRIMARY KEY,
    name      VARCHAR(50)   NOT NULL UNIQUE,
    added_at  TIMESTAMP     DEFAULT NOW()
);
```

---

## ❌ Error Handling

| HTTP Code | Reason |
|---|---|
| `400` | Name is blank or missing |
| `404` | Friend not found (on DELETE) |
| `409` | Friend name already exists |
| `500` | Internal server / database error |

---

## 🖥️ UI Features

- 🌙 Dark theme (`#0F0F1A` background)
- 🔴 Avatar initials auto-generated from first letter of name
- 🔔 Toast notifications replace `printf()` output
- ⌨️ Press **Enter** to add a friend (like `scanf()`)
- 🔢 Live friend count badge updates instantly
- ⚡ Zero page reloads — all calls via Fetch API

---

## 🔐 Security Notes

- All credentials stored in `.env` — **never committed to Git**
- Parameterised SQL queries used throughout — **no SQL injection risk**
- `UNIQUE` constraint + case-insensitive index prevents duplicate entries
- Dedicated DB user recommended for production (see `.env.example`)

---

## 🚀 Future Enhancements

- [ ] JWT-based authentication (per-user friend lists)
- [ ] Search and filter friends in real time
- [ ] Extended profiles (email, phone, avatar)
- [ ] Docker Compose for one-command deployment
- [ ] Jest unit tests for all API routes

---

## 📄 License

MIT License — free to use, modify, and distribute.
