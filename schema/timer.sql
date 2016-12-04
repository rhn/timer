CREATE TABLE Entries(
    id INTEGER PRIMARY KEY,
    description TEXT default "" NOT NULL,
    duration INTEGER,
    start_time INTEGER
);
