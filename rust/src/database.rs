/*! Database procedures */

use chrono::NaiveDateTime;
use crate::schema;
use diesel::sqlite::SqliteConnection;
use once_cell::sync::Lazy;
use std::env;
use std::sync::{ Arc, Mutex };


use diesel::{ Connection, RunQueryDsl, QueryDsl };


type Conn = Arc<Mutex<SqliteConnection>>;

static CONNECTION: Lazy<Conn> = Lazy::new(|| Arc::new(Mutex::new(make_connection())));

mod q {
    #[derive(Queryable, Debug)]
    pub struct Entry {
        id: i32,
        pub description: String,
        pub duration: i32,
        pub start_time: i32,
    }
}

pub struct Entry {
    pub description: String,
    pub duration: i32,
    pub start: String,
}

impl From<q::Entry> for Entry {
    fn from(e: q::Entry) -> Entry {
        Entry {
            description: e.description,
            duration: e.duration,
            start: NaiveDateTime::from_timestamp(e.start_time as i64, 0).format("%Y-%m-%d").to_string(),
        }
    }
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
            .load::<q::Entry>(&*conn)
            .unwrap();
        for entry in entries {
            println!("{:?}", entry);
        }
        Entry {
            description: "text".into(),
            duration: 1,
            start: "9".into(),
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
