/*! Database procedures */

use crate::schema;
use diesel::sqlite::SqliteConnection;
use once_cell::sync::Lazy;
use std::env;
use std::sync::{ Arc, Mutex };


use diesel::{ Connection, RunQueryDsl, QueryDsl };


type Conn = Arc<Mutex<SqliteConnection>>;

static CONNECTION: Lazy<Conn> = Lazy::new(|| Arc::new(Mutex::new(make_connection())));

#[derive(Queryable, Debug)]
pub struct Entry {
    pub id: i32,
    pub description: String,
    pub duration: i32,
    pub start: i32,
}

pub struct Entries {
    connection: Conn,
}

impl Entries {
    pub fn len(&self) -> usize {
        3
    }
    pub fn index(&self, index: usize) -> Entry {
        let conn = self.connection.lock().unwrap();
        use schema::Entries::dsl::*;
        let entries = Entries
            .limit(1)
            .load::<Entry>(&*conn)
            .unwrap();
        for entry in entries {
            println!("{:?}", entry);
        }
        Entry {
            id: 0,
            description: "text".into(),
            duration: 1,
            start: 9,
        }
    }
}
/*
impl Index<usize> for Entries {
    type Output = Entry;
    
}*/

fn make_connection() -> SqliteConnection {
    let db_path = env::var("DATABASE_PATH").unwrap_or("../entries.db".into());
    println!("db: {}", db_path);
    SqliteConnection::establish(&db_path).unwrap()
}

pub fn get_entries() -> Entries {
    Entries { connection: CONNECTION.clone() }
}
