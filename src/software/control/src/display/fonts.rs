use conrod_core::text::font;

pub struct Fonts {
    pub regular: font::Id,
    pub bold: font::Id,
}

impl Fonts {
    pub fn new(regular: font::Id, bold: font::Id) -> Fonts {
        Fonts { regular, bold }
    }
}
