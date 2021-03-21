/*! Database procedures */

use diesel::sqlite::SqliteConnection;
use once_cell::sync::Lazy;
use std::sync::{ Arc, Mutex };


use diesel::Connection;
use std::ops::Index;


type Conn = Arc<Mutex<SqliteConnection>>;

static CONNECTION: Lazy<Conn> = Lazy::new(|| Arc::new(Mutex::new(make_connection())));


pub struct Entry {
    pub description: String,
    pub duration: u32,
    pub start: String,
}

pub struct Entries {
    connection: Conn,
}

impl Entries {
    pub fn len(&self) -> usize {
        3
    }
    pub fn index(&self, index: usize) -> Entry {
        Entry {
            description: "text".into(),
            duration: 1,
            start: "txt".into(),
        }
    }
}
/*
impl Index<usize> for Entries {
    type Output = Entry;
    
}*/

fn make_connection() -> SqliteConnection {
    SqliteConnection::establish("entries.db").unwrap()
}

pub fn get_entries() -> Entries {
    Entries { connection: CONNECTION.clone() }
}
