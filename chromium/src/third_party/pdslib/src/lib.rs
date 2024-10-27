pub mod budget;
pub mod events;
pub mod pds;
pub mod queries;

pub fn add(a: u32, b: u32) -> u32 {
    a + b
}

#[cxx::bridge]
mod ffi {
    extern "Rust" {
        fn add(a: u32, b: u32) -> u32;
    }
}