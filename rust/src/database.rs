/*! Database procedures */

use chrono::{ Duration, NaiveDateTime, Utc };
use crate::schema;
use diesel::sqlite::SqliteConnection;
use once_cell::sync::Lazy;
use std::env;
use std::sync::{ Arc, Mutex };


use diesel::{ Connection, ExpressionMethods, RunQueryDsl, QueryDsl };
use std::ops::Index;
    

type Conn = Arc<Mutex<SqliteConnection>>;

static CONNECTION: Lazy<Conn> = Lazy::new(|| Arc::new(Mutex::new(make_connection())));

mod q {
    use super::schema::Entries;

    #[derive(Queryable, Debug, Clone)]
    pub struct Entry {
        id: i32,
        pub description: String,
        pub duration: i32,
        pub start_time: i32,
    }
    
    #[derive(Insertable)]
    #[table_name="Entries"]
    pub struct NewEntry {
        pub description: String,
        pub duration: i32,
        pub start_time: i32,
    }
}

#[derive(Clone)]
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
    cache: Vec<Entry>,
}

impl Entries {
    pub fn len(&self) -> usize {
       self.cache.len()
    }
    fn query_all(connection: &Conn) -> Vec<Entry> {
        let conn = connection.lock().unwrap();
        use schema::Entries::dsl::*;
        Entries
            .filter(start_time.gt((Utc::now() - Duration::days(32)).timestamp() as i32))
            .order(start_time.desc())
            .load::<q::Entry>(&*conn)
            .unwrap()
            .into_iter()
            .map(Entry::from)
            .collect()
    }
    
    pub fn add_entry(&mut self, duration: u32, description: String) {
        {
            let conn = self.connection.lock().unwrap();
            diesel::insert_into(schema::Entries::table)
                .values(q::NewEntry {
                    description: description.clone(),
                    duration: duration as i32,
                    start_time: Utc::now().timestamp() as i32,
                })
                .execute(&*conn)
                .expect(&format!("Failed to insert duration {} description {:?}", duration, description));
        }
        self.cache = Self::query_all(&self.connection);
    }
}

impl Index<usize> for Entries {
    type Output = Entry;
    fn index(&self, index: usize) -> &Entry {
        &self.cache[index]
    }
}

fn make_connection() -> SqliteConnection {
    let db_path = env::var("DATABASE_PATH").unwrap_or("../entries.db".into());
    println!("db: {}", db_path);
    SqliteConnection::establish(&db_path).unwrap()
}

pub fn get_entries() -> Entries {
    let cache = Entries::query_all(&CONNECTION);
    Entries {
        connection: CONNECTION.clone(),
        cache
    }
}
