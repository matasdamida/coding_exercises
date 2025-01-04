pub struct Vector<T> {
    data: *mut T,
    size: usize,
}

impl<T> Vector<T> {
    pub fn new() -> Self {
        Vector {
            data: std::ptr::null_mut(),
            size: 0,
        }
    }

    pub fn push(&mut self, value: T) {
        // Allocate memory for the new element
        let new_data = unsafe {
            libc::realloc(
                self.data as *mut libc::c_void,
                (self.size + 1) * std::mem::size_of::<T>(),
            ) as *mut T
        };

        // Check if the allocation was successful
        if new_data.is_null() {
            panic!("Memory allocation failed");
        }

        // Update the data pointer
        self.data = new_data;

        // Copy the value to the new element
        unsafe {
            std::ptr::write(self.data.add(self.size), value);
        }

        // Update the size
        self.size += 1;
    }

    pub fn get(&self, index: usize) -> Option<&T> {
        if index < self.size {
            Some(unsafe { &*self.data.add(index) })
        } else {
            None
        }
    }
}
